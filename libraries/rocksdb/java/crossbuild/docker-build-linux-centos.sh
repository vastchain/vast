#!/usr/bin/env bash
# Copyright (c) Facebook, Inc. and its affiliates. All Rights Reserved.

set -e
#set -x

rm -rf /rocksdb-local
cp -r /rocksdb-host /rocksdb-local
cd /rocksdb-local

# Use scl dvastoolset if available (i.e. CentOS <7)
if hash scl 2>/dev/null; then
	if scl --list | grep -q 'dvastoolset-7'; then
		scl enable dvastoolset-7 'make jclean clean'
		scl enable dvastoolset-7 'PORTABLE=1 make -j6 rocksdbjavastatic'
	elif scl --list | grep -q 'dvastoolset-2'; then
		scl enable dvastoolset-2 'make jclean clean'
		scl enable dvastoolset-2 'PORTABLE=1 make -j6 rocksdbjavastatic'
	else
		echo "Could not find dvastoolset"
		exit 1;
	fi
else
	make jclean clean
        PORTABLE=1 make -j6 rocksdbjavastatic
fi

cp java/target/librocksdbjni-linux*.so java/target/rocksdbjni-*-linux*.jar /rocksdb-host/java/target

