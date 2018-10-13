#!/bin/bash

ROHOMEPATH=/nwn/home
HOMEPATH=/nwn/run

function get_children_pids() {
  local my_pid=$$
  echo "$(
    find         \
    /proc/[0-9]* \
    -mindepth 1  \
    -maxdepth 1  \
    -name stat   \
    -exec sed -r -n "/^(\S+)\s+\([^)]+\)\s+[a-zA-Z]\s+${my_pid}\s+.*/{s//\1/p}" {} \+
  )"
}

function get_nwserver_pid() {
  local nwserver_pid="$(
    find                                              \
      /proc/[0-9]*                                    \
      -mindepth 1                                     \
      -maxdepth 1                                     \
      -type l                                         \
      -lname '/nwn/data/bin/linux-x86/nwserver-linux' \
      -regex '/proc/[0-9]+/exe'
  )"
  nwserver_pid="${nwserver_pid%/exe}"
  nwserver_pid="${nwserver_pid#/proc/}"
  echo "$nwserver_pid"
}

function _term () {
  kill -TERM "$(get_nwserver_pid)" 
  wait "$child"
}

trap _term SIGTERM

{
  echo "== $(date) =="
  if ! [ -d "${EFU_ARCHIVED_LOG_DIR}" ]; then
    mkdir -p "${EFU_ARCHIVED_LOG_DIR}"
  fi
  chown :efudm "${EFU_ARCHIVED_LOG_DIR}"
  chmod 750 "${EFU_ARCHIVED_LOG_DIR}"

  for log_file in ${EFU_LOG_FILES}; do
    if ! [ -d "${EFU_ARCHIVED_LOG_DIR}/${log_file}" ]; then
       mkdir -p "${EFU_ARCHIVED_LOG_DIR}/${log_file}"
    fi
    chown :efudm "${EFU_ARCHIVED_LOG_DIR}/${log_file}"
    chmod 750 "${EFU_ARCHIVED_LOG_DIR}/${log_file}"

    archived_log_file="${EFU_ARCHIVED_LOG_DIR}/${log_file}/$(date +%F_%H.%M.%S).txt"
    absolute_log_file=$(find "${EFU_RUN_DIR}" -mindepth 2 -maxdepth 2 -type f -name "${log_file}.txt" | head -n 1)
    if [ -n "${absolute_log_file}" ]; then
      mv "${absolute_log_file}" "${archived_log_file}"
      chown :efudm "${archived_log_file}"
      chmod 640 "${archived_log_file}"
      echo "${archived_log_file} done"
    fi
  done

  # "clean current tables"
  echo '
  UPDATE efusl_module_sessions
  SET end = NOW()
  WHERE end IS NULL
  ORDER BY module_session_id DESC
  LIMIT 1;
  INSERT INTO efusl_sessions (user_id, session_id, login)
  SELECT players.user_id, info.session_id, info.last_login
  FROM efusl_current_players AS players
  JOIN efusl_current_account_info AS info ON players.user_id = info.user_id;
  TRUNCATE TABLE efusl_current_players;
  TRUNCATE TABLE efusl_current_dms;
  ' | mysql --defaults-file="$EFU_MYSQL_CONF" "${NWNX_SQL_DATABASE}" 
} >> "${EFU_RUN_EFU_SERVER_LOG}" 2>&1

# Setup custom nwnx plugin folder 
if [ -d $ROHOMEPATH/nwnx ]; then
    if test -n "$(find $ROHOMEPATH/nwnx -name '*.so' -print -quit)"
    then
        echo "[*] Copying any custom NWNX plugins"
        cp -v $ROHOMEPATH/nwnx/*.so /nwn/nwnx
    fi
    if test -n "$(find $ROHOMEPATH/nwnx -name '*.jar' -print -quit)"
    then
        echo "[*] Copying any custom NWNX jar files"
        cp -v $ROHOMEPATH/nwnx/*.jar /nwn/nwnx
    fi
fi

cd /nwn/data/bin/linux-x86
/nwn/run-server.sh &
child=$!
wait $child
