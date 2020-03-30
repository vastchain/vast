#!/bin/sh
cd /opt/vast/bin

if [ -f '/opt/vast/etc/vastwd/config.ini' ]; then
    echo
  else
    mkdir /opt/vast/etc
    mkdir /opt/vast/etc/vastwd
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
    CONFIG_DIR="--config-dir=/opt/vast/etc/vastwd"
else
    CONFIG_DIR=""
fi

WALLET_DIR="--wallet-dir=/opt/vast/data/wallet"
DATA_DIR="--data-dir=/opt/vast/data/wallet"

exec /opt/vast/bin/vastwd $CONFIG_DIR $DATA_DIR $WALLET_DIR $@
