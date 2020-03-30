#!/bin/sh
cd /opt/vast/bin

if [ -f '/opt/vast/etc/vastd/config.ini' ]; then
    echo
  else
    mkdir /opt/vast/etc
    mkdir /opt/vast/etc/vastd
    cp /config.ini /opt/vast/etc/vastd
fi

while :; do
    case $1 in
        --config-dir=?*)
            CONFIG_DIR=${1#*=}
            ;;
        *)
            break
    esac
    shift
done

if [ ! "$CONFIG_DIR" ]; then
    CONFIG_DIR="--config-dir=/opt/vast/etc/vastd"
else
    CONFIG_DIR=""
fi

DATA_DIR="--data-dir=/opt/vast/data"
SNAPSHOTS_DIR="--snapshots-dir=/opt/vast/snapshots"

exec /opt/vast/bin/vastd $CONFIG_DIR $DATA_DIR $SNAPSHOTS_DIR $@
