#!/bin/bash -ex

set -ex

export PATH=/usr/lib/ccache/bin/:$PATH

cd hiphop-php

git checkout master
git reset --hard facebook/master

git merge --no-ff origin/bugfixes origin/syslog origin/datetime origin/misc origin/loop_documents_sleep

git apply ../datetime_temp.diff
cmake . && make -j4
git apply -R ../datetime_temp.diff
(cd src/system && make)
git apply ../fix_global_symbols.diff
git add src/system/gen/{cls,php,sys,cls} src/runtime/base/{program_functions.cpp,server/http_protocol.cpp}
git commit -m "Regenerate system"

git reset --hard
git checkout test-merge
git reset --hard master

git checkout master
git merge --no-ff origin/libredis origin/memcached-hyves

cmake . && make -j4
(cd src/system && make)
git add src/system/gen/{cls,php,sys,cls}
git commit -m "Regenerate system"

cmake . && make -j4

