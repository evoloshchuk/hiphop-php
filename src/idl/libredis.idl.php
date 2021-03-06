<?php
/**
 * Automatically generated by running "php schema.php libredis".
 *
 * You may modify the file, but re-running schema.php against this file will
 * standardize the format without losing your schema changes. It does lose
 * any changes that are not part of schema. Use "note" field to comment on
 * schema itself, and "note" fields are not used in any code generation but
 * only staying within this file.
 *
 * @nolint
 */
///////////////////////////////////////////////////////////////////////////////
// Preamble: C++ code inserted at beginning of ext_{name}.h

DefinePreamble(<<<CPP
#include <redis.h>
CPP
);

///////////////////////////////////////////////////////////////////////////////
// Constants
//
// array (
//   'name' => name of the constant
//   'type' => type of the constant
//   'note' => additional note about this constant's schema
// )


///////////////////////////////////////////////////////////////////////////////
// Functions
//
// array (
//   'name'   => name of the function
//   'desc'   => description of the function's purpose
//   'flags'  => attributes of the function, see base.php for possible values
//   'opt'    => optimization callback function's name for compiler
//   'note'   => additional note about this function's schema
//   'return' =>
//      array (
//        'type'  => return type, use Reference for ref return
//        'desc'  => description of the return value
//      )
//   'args'   => arguments
//      array (
//        'name'  => name of the argument
//        'type'  => type of the argument, use Reference for output parameter
//        'value' => default value of the argument
//        'desc'  => description of the argument
//      )
// )

DefineFunction(
  array(
    'name'   => "libredis",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Object,
    ),
  ));


///////////////////////////////////////////////////////////////////////////////
// Classes
//
// BeginClass
// array (
//   'name'   => name of the class
//   'desc'   => description of the class's purpose
//   'flags'  => attributes of the class, see base.php for possible values
//   'note'   => additional note about this class's schema
//   'parent' => parent class name, if any
//   'ifaces' => array of interfaces tihs class implements
//   'bases'  => extra internal and special base classes this class requires
//   'footer' => extra C++ inserted at end of class declaration
// )
//
// DefineConstant(..)
// DefineConstant(..)
// ...
// DefineFunction(..)
// DefineFunction(..)
// ...
// DefineProperty
// DefineProperty
//
// array (
//   'name'  => name of the property
//   'type'  => type of the property
//   'flags' => attributes of the property
//   'desc'  => description of the property
//   'note'  => additional note about this property's schema
// )
//
// EndClass()

///////////////////////////////////////////////////////////////////////////////

BeginClass(
  array(
    'name'   => "_Libredis_Ketama",
    'bases'  => array('Sweepable'),
    'flags'  =>  HasDocComment,
    'footer' => <<<EOT

 public:
  Ketama *getKetama();

 private:
  Ketama *m_ketama;
EOT
,
  ));

DefineFunction(
  array(
    'name'   => "__construct",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => null,
    ),
  ));

DefineFunction(
  array(
    'name'   => "add_server",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => null,
    ),
    'args'   => array(
      array(
        'name'   => "host",
        'type'   => String,
      ),
      array(
        'name'   => "port",
        'type'   => Int32,
      ),
      array(
        'name'   => "weight",
        'type'   => Int32,
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "get_server_ordinal",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Int32,
    ),
    'args'   => array(
      array(
        'name'   => "key",
        'type'   => String,
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "get_server_address",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => String,
    ),
    'args'   => array(
      array(
        'name'   => "ordinal",
        'type'   => Int32,
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "create_continuum",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => null,
    ),
  ));

DefineFunction(
  array(
    'name'   => "__destruct",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Variant,
    ),
  ));

EndClass(
);

///////////////////////////////////////////////////////////////////////////////

BeginClass(
  array(
    'name'   => "_Libredis_Executor",
    'bases'  => array('Sweepable'),
    'flags'  =>  HasDocComment,
    'footer' => <<<EOT

 public:
  Executor *getExecutor();

 private:
  Executor *m_executor;
EOT
,
  ));

DefineFunction(
  array(
    'name'   => "__construct",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => null,
    ),
  ));

DefineFunction(
  array(
    'name'   => "add",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Variant,
    ),
    'args'   => array(
      array(
        'name'   => "connection",
        'type'   => Object,
      ),
      array(
        'name'   => "batch",
        'type'   => Object,
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "execute",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Variant,
    ),
    'args'   => array(
      array(
        'name'   => "timeout",
        'type'   => Int32,
        'value'  => "5000",
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "__destruct",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Variant,
    ),
  ));

EndClass(
);

///////////////////////////////////////////////////////////////////////////////

BeginClass(
  array(
    'name'   => "_Libredis_Connection",
    'bases'  => array('Sweepable'),
    'flags'  =>  HasDocComment,
    'footer' => <<<EOT

 public:
  Connection *getConnection();
  bool executeSimple(Batch *batch, int timeout);

 private:
  class ConnectionWrapper {
   public:
    ConnectionWrapper(Connection *c);
    ~ConnectionWrapper();
    Connection *connection;
  };
  typedef boost::shared_ptr<ConnectionWrapper> ConnectionPtr;

  ConnectionPtr m_connection;

  typedef std::map<std::string, ConnectionPtr> ConnectionMap;
  static DECLARE_THREAD_LOCAL(ConnectionMap, s_persistentMap);
EOT
,
  ));

DefineFunction(
  array(
    'name'   => "__construct",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => null,
    ),
    'args'   => array(
      array(
        'name'   => "address",
        'type'   => String,
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "execute",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Boolean,
    ),
    'args'   => array(
      array(
        'name'   => "batch",
        'type'   => Object,
      ),
      array(
        'name'   => "timeout",
        'type'   => Int32,
        'value'  => "5000",
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "set",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Variant,
    ),
    'args'   => array(
      array(
        'name'   => "key",
        'type'   => String,
      ),
      array(
        'name'   => "value",
        'type'   => String,
      ),
      array(
        'name'   => "timeout",
        'type'   => Int32,
        'value'  => "5000",
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "get",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Variant,
    ),
    'args'   => array(
      array(
        'name'   => "key",
        'type'   => String,
      ),
      array(
        'name'   => "timeout",
        'type'   => Int32,
        'value'  => "5000",
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "__destruct",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Variant,
    ),
  ));

EndClass(
);

///////////////////////////////////////////////////////////////////////////////

BeginClass(
  array(
    'name'   => "_Libredis_Batch",
    'bases'  => array('Sweepable'),
    'flags'  =>  HasDocComment,
    'footer' => <<<EOT

 public:
  Batch *getBatch();

 private:
  Batch *m_batch;
EOT
,
  ));

DefineFunction(
  array(
    'name'   => "__construct",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => null,
    ),
  ));

DefineFunction(
  array(
    'name'   => "write",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => null,
    ),
    'args'   => array(
      array(
        'name'   => "str",
        'type'   => String,
      ),
      array(
        'name'   => "num_commands",
        'type'   => Int32,
        'value'  => "0",
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "set",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Object,
    ),
    'args'   => array(
      array(
        'name'   => "key",
        'type'   => String,
      ),
      array(
        'name'   => "value",
        'type'   => String,
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "get",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Object,
    ),
    'args'   => array(
      array(
        'name'   => "key",
        'type'   => String,
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "cmd",
    'flags'  =>  HasDocComment | VariableArguments,
    'return' => array(
      'type'   => null,
    ),
  ));

DefineFunction(
  array(
    'name'   => "next_reply",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Int32,
    ),
    'args'   => array(
      array(
        'name'   => "reply_type",
        'type'   => Variant | Reference,
      ),
      array(
        'name'   => "reply_value",
        'type'   => Variant | Reference,
      ),
      array(
        'name'   => "reply_length",
        'type'   => Variant | Reference,
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "execute",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Boolean,
    ),
    'args'   => array(
      array(
        'name'   => "connection",
        'type'   => Object,
      ),
      array(
        'name'   => "timeout",
        'type'   => Int32,
        'value'  => "5000",
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "__destruct",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Variant,
    ),
  ));

EndClass(
);

///////////////////////////////////////////////////////////////////////////////

BeginClass(
  array(
    'name'   => "_Libredis_Redis",
    'bases'  => array('Sweepable'),
    'flags'  =>  HasDocComment,
    'footer' => <<<EOT

 public:
  static void updateLastError();

 private:
  static DECLARE_THREAD_LOCAL(std::string, m_lastError);
EOT
,
  ));

DefineFunction(
  array(
    'name'   => "__construct",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => null,
    ),
  ));

DefineFunction(
  array(
    'name'   => "create_ketama",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Object,
    ),
  ));

DefineFunction(
  array(
    'name'   => "create_executor",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Object,
    ),
  ));

DefineFunction(
  array(
    'name'   => "last_error",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => String,
    ),
  ));

DefineFunction(
  array(
    'name'   => "get_connection",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Object,
    ),
    'args'   => array(
      array(
        'name'   => "addr",
        'type'   => String,
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "create_batch",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Object,
    ),
    'args'   => array(
      array(
        'name'   => "str",
        'type'   => String,
        'value'  => "null_string",
      ),
      array(
        'name'   => "num_commands",
        'type'   => Int32,
        'value'  => "0",
      ),
    ),
  ));

DefineFunction(
  array(
    'name'   => "__destruct",
    'flags'  =>  HasDocComment,
    'return' => array(
      'type'   => Variant,
    ),
  ));

EndClass(
);

