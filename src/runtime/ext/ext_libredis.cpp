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

#include <runtime/ext/ext_libredis.h>

using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DEFAULT_EXTENSION(libredis);
IMPLEMENT_THREAD_LOCAL(c__Libredis_Connection::ConnectionMap,
                       c__Libredis_Connection::s_persistentMap);
IMPLEMENT_THREAD_LOCAL(std::string, c__Libredis_Redis::m_lastError);

namespace {
class LibredisModule {
public:
  LibredisModule() {
    module = Module_new();
    Module_init(module);
  }

  ~LibredisModule() {
    Module_free(module);
  }

  Module *module;
};

static LibredisModule s_libredis_module;
}

Object f_libredis() {
  return p__Libredis_Redis(NEWOBJ(c__Libredis_Redis)())->create();
}

///////////////////////////////////////////////////////////////////////////////
// class _Libredis_Ketama

c__Libredis_Ketama::c__Libredis_Ketama(const ObjectStaticCallbacks *cb)
  : ExtObjectData(cb), m_ketama(Ketama_new()) { }
c__Libredis_Ketama::~c__Libredis_Ketama() {
  Ketama_free(m_ketama);
}

void c__Libredis_Ketama::t___construct() { }

Variant c__Libredis_Ketama::t___destruct() {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Ketama, _Libredis_Ketama::__destruct);
  return null;
}

Ketama *c__Libredis_Ketama::getKetama() {
  return m_ketama;
}

void c__Libredis_Ketama::t_add_server(CStrRef host, int port, int weight) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Ketama, _Libredis_Ketama::add_server);
  Ketama_add_server(m_ketama, host.c_str(), port, weight);
}

int c__Libredis_Ketama::t_get_server_ordinal(CStrRef key) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Ketama, _Libredis_Ketama::get_server_ordinal);
  return Ketama_get_server_ordinal(m_ketama, key.c_str(), key.length());
}

String c__Libredis_Ketama::t_get_server_address(int ordinal) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Ketama, _Libredis_Ketama::get_server_address);
  return String(Ketama_get_server_address(m_ketama, ordinal), CopyString);
}

void c__Libredis_Ketama::t_create_continuum() {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Ketama, _Libredis_Ketama::create_continuum);
  Ketama_create_continuum(m_ketama);
}

///////////////////////////////////////////////////////////////////////////////
// class _Libredis_Executor

c__Libredis_Executor::c__Libredis_Executor(const ObjectStaticCallbacks *cb)
  : ExtObjectData(cb), m_executor(Executor_new()) { }
c__Libredis_Executor::~c__Libredis_Executor() {
  Executor_free(m_executor);
}

void c__Libredis_Executor::t___construct() { }

Variant c__Libredis_Executor::t___destruct() {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Executor, _Libredis_Executor::__destruct);
  return null;
}

Executor *c__Libredis_Executor::getExecutor() {
  return m_executor;
}

Variant c__Libredis_Executor::t_add(CObjRef connection, CObjRef batch) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Executor, _Libredis_Executor::add);
  c__Libredis_Connection *typedConnection =
      connection.getTyped<c__Libredis_Connection>();
  c__Libredis_Batch *typedBatch =
      batch.getTyped<c__Libredis_Batch>();
  Connection *redisConnection = typedConnection->getConnection();
  if (!redisConnection || Executor_add(m_executor, redisConnection,
                   typedBatch->getBatch()) == -1) {
    return null;
  }
  return true;
}

Variant c__Libredis_Executor::t_execute(int timeout /*= 5000*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Executor, _Libredis_Executor::execute);
  int res = Executor_execute(m_executor, timeout);
  if (res > 0) {
    return true;
  } else if (res == 0) {
    c__Libredis_Redis::updateLastError();
    return false;
  } else {
    raise_error("%s", Module_last_error(s_libredis_module.module));
    return null;
  }
}

///////////////////////////////////////////////////////////////////////////////
// class _Libredis_Connection

namespace {
class ExecutorWrapper {
public:
  ExecutorWrapper() : executor(Executor_new()) { }
  ~ExecutorWrapper() { Executor_free(executor); }
  Executor *executor;
};

class BatchWrapper {
public:
  BatchWrapper() : batch(Batch_new()) { }
  ~BatchWrapper() { Batch_free(batch); }
  Batch *batch;
};
}

c__Libredis_Connection::ConnectionWrapper::ConnectionWrapper(Connection *c)
  : connection(c) { }
c__Libredis_Connection::ConnectionWrapper::~ConnectionWrapper() {
  Connection_free(connection);
}

c__Libredis_Connection::c__Libredis_Connection(const ObjectStaticCallbacks *cb)
  : ExtObjectData(cb)  { }
c__Libredis_Connection::~c__Libredis_Connection() { }

void c__Libredis_Connection::t___construct(CStrRef address) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Connection, _Libredis_Connection::__construct);
  ConnectionPtr &connection = (*s_persistentMap)[address.c_str()];
  if (!connection) {
    Connection *newConnection = Connection_new(address);
    if (!newConnection) {
      raise_error("%s", Module_last_error(s_libredis_module.module));
      return;
    }
    connection.reset(new ConnectionWrapper(newConnection));
  }
  m_connection = connection;
}

Variant c__Libredis_Connection::t___destruct() {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Connection, _Libredis_Connection::__destruct);
  return null;
}

Connection *c__Libredis_Connection::getConnection() {
  return m_connection ? m_connection->connection : NULL;
}

bool c__Libredis_Connection::executeSimple(Batch *batch, int timeout) {
  Connection *redisConnection = getConnection();
  if (!redisConnection)
    return false;
  ExecutorWrapper executor;
  Executor_add(executor.executor, redisConnection, batch);
  int res = Executor_execute(executor.executor, timeout);
  if (res < 0) {
    raise_error("%s", Module_last_error(s_libredis_module.module));
  }
  return res == 1;
}

bool c__Libredis_Connection::t_execute(CObjRef batch, int timeout /*= 5000*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Connection, _Libredis_Connection::execute);
  c__Libredis_Batch *typedBatch = batch.getTyped<c__Libredis_Batch>();
  return executeSimple(typedBatch->getBatch(), timeout);
}

Variant c__Libredis_Connection::t_set(CStrRef key, CStrRef value,
                                      int timeout /*= 5000*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Connection, _Libredis_Connection::set);
  BatchWrapper batch;
  Batch_write_set(batch.batch, key.c_str(), key.length(),
                  value.c_str(), value.length());
  if (!executeSimple(batch.batch, timeout)) {
    c__Libredis_Redis::updateLastError();
    return false;
  }
  ReplyType replyType; char *replyValue; size_t replyLength;
  int level = Batch_next_reply(batch.batch, &replyType,
                               &replyValue, &replyLength);
  if (level != 1) {
    raise_error("Unexpected level");
    return null;
  } else if (replyType == RT_OK) {
    return true;
  } else if (replyType == RT_ERROR) {
    c__Libredis_Redis::updateLastError();
    return false;
  } else {
    raise_error("Unexpected reply type");
    return null;
  }
}

Variant c__Libredis_Connection::t_get(CStrRef key, int timeout /*= 5000*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Connection, _Libredis_Connection::get);
  BatchWrapper batch;
  Batch_write_get(batch.batch, key.c_str(), key.length());
  if (!executeSimple(batch.batch, timeout)) {
    c__Libredis_Redis::updateLastError();
    return false;
  }
  ReplyType replyType; char *replyValue; size_t replyLength;
  int level = Batch_next_reply(batch.batch, &replyType,
                               &replyValue, &replyLength);
  if (level != 1) {
    raise_error("Unexpected level");
    return null;
  } else if (replyType == RT_BULK) {
    if (replyValue && replyLength > 0) {
      return String(replyValue, replyLength, CopyString);
    } else {
      return empty_string;
    }
  } else if (replyType == RT_BULK_NIL) {
    return null;
  } else if (replyType == RT_ERROR) {
    c__Libredis_Redis::updateLastError();
    return false;
  } else {
    raise_error("Unexpected reply type");
    return null;
  }
}

///////////////////////////////////////////////////////////////////////////////
// class _Libredis_Batch

c__Libredis_Batch::c__Libredis_Batch(const ObjectStaticCallbacks *cb)
  : ExtObjectData(cb), m_batch(Batch_new()) { }
c__Libredis_Batch::~c__Libredis_Batch() {
  Batch_free(m_batch);
}

void c__Libredis_Batch::t___construct() { }

Variant c__Libredis_Batch::t___destruct() {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Batch, _Libredis_Batch::__destruct);
  return null;
}

Batch *c__Libredis_Batch::getBatch() {
  return m_batch;
}

void c__Libredis_Batch::t_write(CStrRef str, int num_commands /*= 0*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Batch, _Libredis_Batch::write);
  Batch_write(m_batch, str.c_str(), str.length(), num_commands);
}

Object c__Libredis_Batch::t_set(CStrRef key, CStrRef value) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Batch, _Libredis_Batch::set);
  Batch_write_set(m_batch, key.c_str(), key.length(),
                  value.c_str(), value.length());
  return this;
}

Object c__Libredis_Batch::t_get(CStrRef key) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Batch, _Libredis_Batch::get);
  Batch_write_get(m_batch, key.c_str(), key.length());
  return this;
}

void c__Libredis_Batch::t_cmd(int _argc, CArrRef _argv /*= null_array*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Batch, _Libredis_Batch::cmd);
  for (ArrayIter iter(_argv); iter; ++iter) {
    if (!iter.second().isString()) {
      raise_error("all arguments must be strings!");
      return;
    }
  }
  Batch_write(m_batch, "*", 1, 1);
  Batch_write_decimal(m_batch, _argc);
  Batch_write(m_batch, "\r\n", 2, 0);
  for (ArrayIter iter(_argv); iter; ++iter) {
    String value = iter.second().toString();
    Batch_write(m_batch, "$", 1, 0);
    Batch_write_decimal(m_batch, value.length());
    Batch_write(m_batch, "\r\n", 2, 0);
    Batch_write(m_batch, value.c_str(), value.length(), 0);
    Batch_write(m_batch, "\r\n", 2, 0);
  }
}

int c__Libredis_Batch::t_next_reply(VRefParam reply_type,
                                    VRefParam reply_value,
                                    VRefParam reply_length) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Batch, _Libredis_Batch::next_reply);
  ReplyType replyType; char *replyValue; size_t replyLength;
  int level = Batch_next_reply(m_batch, &replyType, &replyValue, &replyLength);
  reply_type = replyType;
  switch (replyType) {
  case RT_OK:
  case RT_ERROR:
  case RT_BULK:
    if (replyValue && replyLength > 0) {
      reply_value = String(replyValue, replyLength, CopyString);
    } else {
      reply_value = empty_string;
    }
    break;
  case RT_INTEGER:
    reply_value = (int)strtol(replyValue, NULL, 10);
    break;
  default:
    reply_value = null;
    break;
  }
  reply_length = (int)replyLength;
  return level;
}

bool c__Libredis_Batch::t_execute(CObjRef connection, int timeout /*= 5000*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Batch, _Libredis_Batch::execute);
  c__Libredis_Connection *typedConnection =
      connection.getTyped<c__Libredis_Connection>();
  return typedConnection->executeSimple(m_batch, timeout);
}

///////////////////////////////////////////////////////////////////////////////
// class _Libredis_Redis

c__Libredis_Redis::c__Libredis_Redis(const ObjectStaticCallbacks *cb)
  : ExtObjectData(cb)    { }
c__Libredis_Redis::~c__Libredis_Redis()   { }

void c__Libredis_Redis::t___construct() { }

Variant c__Libredis_Redis::t___destruct() {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Redis, _Libredis_Redis::__destruct);
  return null;
}

void c__Libredis_Redis::updateLastError() {
  *m_lastError = Module_last_error(s_libredis_module.module);
}

Object c__Libredis_Redis::t_create_ketama() {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Redis, _Libredis_Redis::create_ketama);
  return p__Libredis_Ketama(NEWOBJ(c__Libredis_Ketama))->create();
}

Object c__Libredis_Redis::t_create_executor() {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Redis, _Libredis_Redis::create_executor);
  return p__Libredis_Executor(NEWOBJ(c__Libredis_Executor))->create();
}

String c__Libredis_Redis::t_last_error() {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Redis, _Libredis_Redis::last_error);
  return *m_lastError;
}

Object c__Libredis_Redis::t_get_connection(CStrRef addr) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Redis, _Libredis_Redis::get_connection);
  return p__Libredis_Connection(NEWOBJ(c__Libredis_Connection))->create(addr);
}

Object c__Libredis_Redis::t_create_batch(CStrRef str /*= null_string*/,
                                         int num_commands /*= 0*/) {
  INSTANCE_METHOD_INJECTION_BUILTIN(_Libredis_Redis, _Libredis_Redis::create_batch);
  p__Libredis_Batch batch(p__Libredis_Batch(
    NEWOBJ(c__Libredis_Batch))->create());
  if (!str.isNull()) {
    batch->t_write(str, num_commands);
  }
  return batch;
}

///////////////////////////////////////////////////////////////////////////////
}
