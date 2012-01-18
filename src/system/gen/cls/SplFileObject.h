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

#ifndef __GENERATED_cls$$SplFileObject$_h__
#define __GENERATED_cls$$SplFileObject$_h__

#include <runtime/base/hphp_system.h>
#include <system/gen/sys/literal_strings_remap.h>
#include <system/gen/sys/scalar_arrays_remap.h>
#include <cls/SplFileInfo.h>
#include <cls/RecursiveIterator.h>
#include <cls/Traversable.h>
#include <cls/SeekableIterator.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

extern StaticString s_sys_ss7e5fc106;
extern StaticString s_sys_ssd332baa7;
extern StaticString s_sys_ssd59e789f;
extern StaticString s_sys_ss0d42ecf6;

extern VarNR s_sys_svs7e5fc106;
extern VarNR s_sys_svsd332baa7;
extern VarNR s_sys_svsd59e789f;
extern VarNR s_sys_svs0d42ecf6;

/* SRC: classes/splfile.php line 384 */
FORWARD_DECLARE_CLASS(SplFileObject);
extern const ObjectStaticCallbacks cw_SplFileObject;
class c_SplFileObject : public c_SplFileInfo {
  public:

  // Properties

  // Class Map
  DECLARE_CLASS_NO_SWEEP(SplFileObject, SplFileObject, SplFileInfo)
  static const ClassPropTable os_prop_table;
  c_SplFileObject(const ObjectStaticCallbacks *cb = &cw_SplFileObject) : c_SplFileInfo(cb) {}
  public: void t___construct(Variant v_filename, Variant v_open_mode = NAMSTR(s_sys_ss0d42ecf6, "r"), Variant v_use_include_path = false, Variant v_context = null);
  public: c_SplFileObject *create(CVarRef v_filename, CVarRef v_open_mode = NAMVAR(s_sys_svs0d42ecf6, "r"), CVarRef v_use_include_path = false_varNR, CVarRef v_context = null_variant);
  public: Variant t_current();
  public: bool t_eof();
  public: bool t_fflush();
  public: String t_fgetc();
  public: Variant t_fgetcsv(CVarRef v_delimiter = NAMVAR(s_sys_svsd332baa7, ","), CVarRef v_enclosure = NAMVAR(s_sys_svs7e5fc106, "\""), CVarRef v_escape = NAMVAR(s_sys_svsd59e789f, "\\"));
  public: String t_fgets();
  public: String t_fgetss(CVarRef v_allowable_tags);
  public: bool t_flock(CVarRef v_operation, VRefParam rv_wouldblock);
  public: int64 t_fpassthru();
  public: Variant t_fscanf(int num_args, CVarRef v_format, Array args = Array());
  public: int64 t_fseek(CVarRef v_offset, CVarRef v_whence);
  public: Variant t_fstat();
  public: int64 t_ftell();
  public: bool t_ftruncate(CVarRef v_size);
  public: int64 t_fwrite(CVarRef v_str, CVarRef v_length);
  public: Variant t_getchildren();
  public: Variant t_getcsvcontrol();
  public: int64 t_getflags();
  public: int64 t_getmaxlinelen();
  public: bool t_haschildren();
  public: int64 t_key();
  public: void t_next();
  public: void t_rewind();
  public: void t_seek(CVarRef v_line_pos);
  public: void t_setcsvcontrol(CVarRef v_delimiter = NAMVAR(s_sys_svsd332baa7, ","), CVarRef v_enclosure = NAMVAR(s_sys_svs7e5fc106, "\""), CVarRef v_escape = NAMVAR(s_sys_svsd59e789f, "\\"));
  public: void t_setflags(CVarRef v_flags);
  public: void t_setmaxlinelen(CVarRef v_max_len);
  public: bool t_valid();
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  DECLARE_METHOD_INVOKE_HELPERS(current);
  DECLARE_METHOD_INVOKE_HELPERS(eof);
  DECLARE_METHOD_INVOKE_HELPERS(fflush);
  DECLARE_METHOD_INVOKE_HELPERS(fgetc);
  DECLARE_METHOD_INVOKE_HELPERS(fgetcsv);
  DECLARE_METHOD_INVOKE_HELPERS(fgets);
  DECLARE_METHOD_INVOKE_HELPERS(fgetss);
  DECLARE_METHOD_INVOKE_HELPERS(flock);
  DECLARE_METHOD_INVOKE_HELPERS(fpassthru);
  DECLARE_METHOD_INVOKE_HELPERS(fscanf);
  DECLARE_METHOD_INVOKE_HELPERS(fseek);
  DECLARE_METHOD_INVOKE_HELPERS(fstat);
  DECLARE_METHOD_INVOKE_HELPERS(ftell);
  DECLARE_METHOD_INVOKE_HELPERS(ftruncate);
  DECLARE_METHOD_INVOKE_HELPERS(fwrite);
  DECLARE_METHOD_INVOKE_HELPERS(getchildren);
  DECLARE_METHOD_INVOKE_HELPERS(getcsvcontrol);
  DECLARE_METHOD_INVOKE_HELPERS(getflags);
  DECLARE_METHOD_INVOKE_HELPERS(getmaxlinelen);
  DECLARE_METHOD_INVOKE_HELPERS(haschildren);
  DECLARE_METHOD_INVOKE_HELPERS(key);
  DECLARE_METHOD_INVOKE_HELPERS(next);
  DECLARE_METHOD_INVOKE_HELPERS(rewind);
  DECLARE_METHOD_INVOKE_HELPERS(seek);
  DECLARE_METHOD_INVOKE_HELPERS(setcsvcontrol);
  DECLARE_METHOD_INVOKE_HELPERS(setflags);
  DECLARE_METHOD_INVOKE_HELPERS(setmaxlinelen);
  DECLARE_METHOD_INVOKE_HELPERS(valid);
};
ObjectData *coo_SplFileObject() NEVER_INLINE;
extern const int64 q_SplFileObject$$DROP_NEW_LINE;
extern const int64 q_SplFileObject$$READ_AHEAD;
extern const int64 q_SplFileObject$$SKIP_EMPTY;
extern const int64 q_SplFileObject$$READ_CSV;

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_cls$$SplFileObject$_h__
