/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Hyves (http://www.hyves.nl)                       |
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   | Copyright (c) 1997-2010 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include <test/test_ext_libredis.h>
#include <runtime/ext/ext_libredis.h>

IMPLEMENT_SEP_EXTENSION_TEST(Libredis);
///////////////////////////////////////////////////////////////////////////////

bool TestExtLibredis::RunTests(const std::string &which) {
  bool ret = true;

  RUN_TEST(test_libredis);
  RUN_TEST(test__Libredis_Ketama);
  RUN_TEST(test__Libredis_Executor);
  RUN_TEST(test__Libredis_Connection);
  RUN_TEST(test__Libredis_Batch);
  RUN_TEST(test__Libredis_Redis);

  return ret;
}

///////////////////////////////////////////////////////////////////////////////

bool TestExtLibredis::test_libredis() {
  return Count(true);
}

bool TestExtLibredis::test__Libredis_Ketama() {
  return Count(true);
}

bool TestExtLibredis::test__Libredis_Executor() {
  return Count(true);
}

bool TestExtLibredis::test__Libredis_Connection() {
  return Count(true);
}

bool TestExtLibredis::test__Libredis_Batch() {
  return Count(true);
}

bool TestExtLibredis::test__Libredis_Redis() {
  return Count(true);
}
