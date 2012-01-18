/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
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
// @generated by HipHop Compiler

#ifndef __GENERATED_cls$$ReflectionException$_h__
#define __GENERATED_cls$$ReflectionException$_h__

#include <runtime/base/hphp_system.h>
#include <system/gen/sys/literal_strings_remap.h>
#include <system/gen/sys/scalar_arrays_remap.h>
#include <cls/Exception.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* SRC: classes/reflection.php line 27 */
FORWARD_DECLARE_CLASS(ReflectionException);
extern const ObjectStaticCallbacks cw_ReflectionException;
class c_ReflectionException : public c_Exception {
  public:

  // Properties

  // Class Map
  DECLARE_CLASS_COMMON_NO_SWEEP(ReflectionException, ReflectionException)

  // DECLARE_STATIC_PROP_OPS
  public:

  // DECLARE_COMMON_INVOKE
  static const int s_call_info_table = 0;
  static const int s_call_info_index = 0;

  public:
  c_ReflectionException(const ObjectStaticCallbacks *cb = &cw_ReflectionException) : c_Exception(cb) {}
};
ObjectData *coo_ReflectionException() NEVER_INLINE;

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_cls$$ReflectionException$_h__
