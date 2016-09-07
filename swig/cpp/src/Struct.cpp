/**
 * @file Struct.cpp
 * @author Mislav Novakovic <mislav.novakovic@sartura.hr>
 * @brief Sysrepo class header implementation for C struts.
 *
 * @copyright
 * Copyright 2016 Deutsche Telekom AG.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <memory>

#include "Struct.h"
#include "Sysrepo.h"

extern "C" {
#include "sysrepo.h"
}

using namespace std;

Operation::Operation(sr_change_oper_t oper) {_oper = oper;}
Operation::~Operation() {return;}

// Data
Data::Data(sr_data_t data, sr_type_t type) {_d = data; _t = type;}
Data::~Data() {return;}
char *Data::get_binary() {
    if (_t != SR_BINARY_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.binary_val;
}
char *Data::get_bits() {
    if (_t != SR_BITS_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.bits_val;
}
bool Data::get_bool() {
    if (_t != SR_BOOL_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.bool_val;
}
double Data::get_decimal64() {
    if (_t != SR_DECIMAL64_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.decimal64_val;
}
char *Data::get_enum() {
    if (_t != SR_ENUM_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.enum_val;
}
char *Data::get_identityref() {
    if (_t != SR_IDENTITYREF_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.identityref_val;
}
char *Data::get_instanceid() {
    if (_t != SR_INSTANCEID_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.instanceid_val;
}
int8_t Data::get_int8() {
    if (_t != SR_INT8_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.int8_val;
}
int16_t Data::get_int16() {
    if (_t != SR_INT16_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.uint32_val;
}
int32_t Data::get_int32() {
    if (_t != SR_INT32_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.int32_val;
}
int64_t Data::get_int64() {
    if (_t != SR_INT64_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.int64_val;
}
char *Data::get_string() {
    if (_t != SR_STRING_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.string_val;
}
uint8_t Data::get_uint8() {
    if (_t != SR_UINT8_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.uint32_val;
}
uint16_t Data::get_uint16() {
    if (_t != SR_UINT16_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.uint16_val;
}
uint32_t Data::get_uint32() {
    if (_t != SR_UINT32_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.uint32_val;
}
uint64_t Data::get_uint64() {
    if (_t != SR_UINT64_T) throw_exception(SR_ERR_DATA_MISSING);
    return _d.uint64_val;
}

// Val
Val::Val(sr_val_t *val, bool free) {
    if (val == NULL)
        throw_exception(SR_ERR_INVAL_ARG);
    _val = val;
    _free = free;
}
Val::~Val() {
    if (_free && _val != NULL)
        sr_free_val(_val);
    return;
}
Val::Val(const char *value, sr_type_t type) {
    sr_val_t *val = NULL;
    val = (sr_val_t*) calloc(1, sizeof(sr_val_t));
    if (val == NULL)
        throw_exception(SR_ERR_NOMEM);
    if (type == SR_BINARY_T) {
	val->data.binary_val = (char *) value;
    } else if (type == SR_BITS_T) {
	val->data.bits_val = (char *) value;
    } else if (type == SR_ENUM_T) {
	val->data.enum_val = (char *) value;
    } else if (type == SR_IDENTITYREF_T) {
	val->data.identityref_val = (char *) value;
    } else if (type == SR_INSTANCEID_T) {
	val->data.instanceid_val = (char *) value;
    } else if (type == SR_STRING_T) {
	val->data.string_val = (char *) value;
    } else {
        free(val);
        throw_exception(SR_ERR_INVAL_ARG);
    }

    val->type = type;
    _val = val;
}
Val::Val(bool bool_val, sr_type_t type) {
    sr_val_t *val = NULL;
    val = (sr_val_t*) calloc(1, sizeof(sr_val_t));
    if (val == NULL)
        throw_exception(SR_ERR_NOMEM);
    if (type == SR_BOOL_T) {
	val->data.bool_val = bool_val;
    } else {
        free(val);
        throw_exception(SR_ERR_INVAL_ARG);
    }

    val->type = type;
    _val = val;
}
Val::Val(double decimal64_val, sr_type_t type) {
    sr_val_t *val = NULL;
    val = (sr_val_t*) calloc(1, sizeof(sr_val_t));
    if (val == NULL)
        throw_exception(SR_ERR_NOMEM);
    if (type == SR_DECIMAL64_T) {
	val->data.decimal64_val = decimal64_val;
    } else {
        free(val);
        throw_exception(SR_ERR_INVAL_ARG);
    }

    val->type = type;
    _val = val;
}
Val::Val(int8_t int8_val, sr_type_t type) {
    sr_val_t *val = NULL;
    val = (sr_val_t*) calloc(1, sizeof(sr_val_t));
    if (val == NULL)
        throw_exception(SR_ERR_NOMEM);
    if (type == SR_INT8_T) {
	val->data.int8_val = int8_val;
    } else {
        free(val);
        throw_exception(SR_ERR_INVAL_ARG);
    }

    val->type = type;
    _val = val;
}
Val::Val(int16_t int16_val, sr_type_t type) {
    sr_val_t *val = NULL;
    val = (sr_val_t*) calloc(1, sizeof(sr_val_t));
    if (val == NULL)
        throw_exception(SR_ERR_NOMEM);
    if (type == SR_INT16_T) {
	val->data.int16_val = int16_val;
    } else {
        free(val);
        throw_exception(SR_ERR_INVAL_ARG);
    }

    val->type = type;
    _val = val;
}
Val::Val(int32_t int32_val, sr_type_t type) {
    sr_val_t *val = NULL;
    val = (sr_val_t*) calloc(1, sizeof(sr_val_t));
    if (val == NULL)
        throw_exception(SR_ERR_NOMEM);
    if (type == SR_INT32_T) {
	val->data.int32_val = int32_val;
    } else {
        free(val);
        throw_exception(SR_ERR_INVAL_ARG);
    }

    val->type = type;
    _val = val;
}
Val::Val(int64_t int64_val, sr_type_t type) {
    sr_val_t *val = NULL;
    val = (sr_val_t*) calloc(1, sizeof(sr_val_t));
    if (val == NULL)
        throw_exception(SR_ERR_NOMEM);
    if (type == SR_DECIMAL64_T) {
	val->data.uint64_val = (double) int64_val;
    } else if (type == SR_UINT64_T) {
        val->data.uint64_val = (uint64_t) int64_val;
    } else if (type == SR_UINT32_T) {
        val->data.uint32_val = (uint32_t) int64_val;
    } else if (type == SR_UINT16_T) {
        val->data.uint16_val = (uint16_t) int64_val;
    } else if (type == SR_UINT8_T) {
        val->data.uint8_val = (uint8_t) int64_val;
    } else if (type == SR_INT64_T) {
        val->data.int64_val = (int64_t) int64_val;
    } else if (type == SR_INT32_T) {
        val->data.int32_val = (int32_t) int64_val;
    } else if (type == SR_INT16_T) {
        val->data.int16_val = (int16_t) int64_val;
    } else if (type == SR_INT8_T) {
        val->data.int8_val = (int8_t) int64_val;
    } else {
	    printf("\nERROR \n\n\n\n");
        free(val);
        throw_exception(SR_ERR_INVAL_ARG);
    }

    val->type = type;
    _val = val;
}
Val::Val(uint8_t uint8_val, sr_type_t type) {
    sr_val_t *val = NULL;
    val = (sr_val_t*) calloc(1, sizeof(sr_val_t));
    if (val == NULL)
        throw_exception(SR_ERR_NOMEM);
    if (type == SR_UINT8_T) {
	val->data.uint8_val = uint8_val;
    } else {
        free(val);
        throw_exception(SR_ERR_INVAL_ARG);
    }

    val->type = type;
    _val = val;
}
Val::Val(uint16_t uint16_val, sr_type_t type) {
    sr_val_t *val = NULL;
    val = (sr_val_t*) calloc(1, sizeof(sr_val_t));
    if (val == NULL)
        throw_exception(SR_ERR_NOMEM);
    if (type == SR_UINT16_T) {
	val->data.uint16_val = uint16_val;
    } else {
        free(val);
        throw_exception(SR_ERR_INVAL_ARG);
    }

    val->type = type;
    _val = val;
}
Val::Val(uint32_t uint32_val, sr_type_t type) {
    sr_val_t *val = NULL;
    val = (sr_val_t*) calloc(1, sizeof(sr_val_t));
    if (val == NULL)
        throw_exception(SR_ERR_NOMEM);
    if (type == SR_UINT32_T) {
	val->data.uint32_val = uint32_val;
    } else {
        free(val);
        throw_exception(SR_ERR_INVAL_ARG);
    }

    val->type = type;
    _val = val;
}
Val::Val(uint64_t uint64_val, sr_type_t type) {
    sr_val_t *val = NULL;
    val = (sr_val_t*) calloc(1, sizeof(sr_val_t));
    if (val == NULL)
        throw_exception(SR_ERR_NOMEM);
    if (type == SR_UINT64_T) {
	val->data.uint64_val = uint64_val;
    } else {
        free(val);
        throw_exception(SR_ERR_INVAL_ARG);
    }

    val->type = type;
    _val = val;
}

/// Val_Holder
Val_Holder::Val_Holder(sr_val_t *val) {_val = val;}
Val_Holder::~Val_Holder() {
    if (_val != NULL)
        sr_free_val(_val);
    return;
}
shared_ptr<Val> Val_Holder::val() {
    if (_val == NULL)
        return NULL;
    shared_ptr<Val> val(new Val(_val, false));
    return val;
}
// Vals
Vals::Vals(sr_val_t *vals, size_t cnt) {_vals = vals; _cnt = cnt;}
Vals::~Vals() {
    if (_vals != NULL)
        sr_free_values(_vals, _cnt);
    return;
}
shared_ptr<Val> Vals::val(size_t n) {
    if (n >= _cnt)
        return NULL;

    shared_ptr<Val> val(new Val(&_vals[n], false));
    return val;
}

// Val_iter
Val_Iter::Val_Iter(sr_val_iter_t *iter) {_iter = iter;}
Val_Iter::~Val_Iter() {return;}

// Change_Iter
Change_Iter::Change_Iter(sr_change_iter_t *iter) {_iter = iter;}
Change_Iter::~Change_Iter() {return;}

// Error
Error::Error(const sr_error_info_t *info) {_info = info;}
Error::~Error() {return;}

// Errors
Errors::Errors(const sr_error_info_t *info, size_t cnt) {_info = info; _cnt = cnt;}
Errors::~Errors() {return;}
shared_ptr<Error> Errors::error(size_t n) {
    if (n >= _cnt)
        return NULL;

    shared_ptr<Error> error(new Error(&_info[n]));
    return error;
}

// Node
Node::Node(const sr_node_t *node) {_node = node;}
Node::~Node() {return;}
shared_ptr<Node> Node::parent() {
    if (_node->parent == NULL)
        return NULL;

    shared_ptr<Node> node(new Node(_node->parent));
    return NULL;
}
shared_ptr<Node> Node::next() {
    if (_node->next == NULL)
        return NULL;

    shared_ptr<Node> node(new Node(_node->next));
    return NULL;
}
shared_ptr<Node> Node::prev() {
    if (_node->prev == NULL)
        return NULL;

    shared_ptr<Node> node(new Node(_node->prev));
    return NULL;
}
shared_ptr<Node> Node::first_child() {
    if (_node->first_child == NULL)
        return NULL;

    shared_ptr<Node> node(new Node(_node->first_child));
    return NULL;
}
shared_ptr<Node> Node::last_child() {
    if (_node->last_child == NULL)
        return NULL;

    shared_ptr<Node> node(new Node(_node->last_child));
    return NULL;
}

// Schema_Revision
Schema_Revision::Schema_Revision(sr_sch_revision_t rev) {_rev = rev;}
Schema_Revision::~Schema_Revision() {return;}

// Schema_Submodule
Schema_Submodule::Schema_Submodule(sr_sch_submodule_t sub) {_sub = sub;}
Schema_Submodule::~Schema_Submodule() {return;}
shared_ptr<Schema_Revision> Schema_Submodule::revision() {
    shared_ptr<Schema_Revision> rev(new Schema_Revision(_sub.revision));
    return rev;
}

// Yang_Schema
Yang_Schema::Yang_Schema(sr_schema_t *sch) {_sch = sch;}
Yang_Schema::~Yang_Schema() {return;}
shared_ptr<Schema_Revision> Yang_Schema::revision() {
    shared_ptr<Schema_Revision> rev(new Schema_Revision(_sch->revision));
    return rev;
}
shared_ptr<Schema_Submodule> Yang_Schema::submodule(size_t n) {
    if (n >= _sch->submodule_count)
        return NULL;

    shared_ptr<Schema_Submodule> sub(new Schema_Submodule(_sch->submodules[n]));
    return sub;
}
char *Yang_Schema::enabled_features(size_t n) {
    if (n >= _sch->enabled_feature_cnt)
        return NULL;

   return _sch->enabled_features[n];
}

// Yang_Schemas
Yang_Schemas::Yang_Schemas(sr_schema_t *sch, size_t cnt) {_sch = sch; _cnt = cnt;}
Yang_Schemas::~Yang_Schemas() {return;}
shared_ptr<Yang_Schema> Yang_Schemas::schema(size_t n) {
    if (n >= _cnt)
        return NULL;

    shared_ptr<Yang_Schema> rev(new Yang_Schema((sr_schema_t *) &_sch[n]));
    return rev;
}

// Fd_Change
Fd_Change::Fd_Change(sr_fd_change_t *ch) {_ch = ch;}
Fd_Change::~Fd_Change() {return;}

// Fd_Changes
Fd_Changes::Fd_Changes(sr_fd_change_t *ch, size_t cnt) {_ch = ch; _cnt = cnt;}
Fd_Changes::~Fd_Changes() {return;}
shared_ptr<Fd_Change> Fd_Changes::fd_change(size_t n) {
    if (n >= _cnt)
        return NULL;

    shared_ptr<Fd_Change> change(new Fd_Change(&_ch[n]));
    return change;
}

Iter_Value::Iter_Value(sr_val_iter_t *iter) {_iter = iter;}
Iter_Value::~Iter_Value() {if (_iter) sr_free_val_iter(_iter);}
void Iter_Value::Set(sr_val_iter_t *iter) {
    if (_iter)
        sr_free_val_iter(_iter);
    _iter = iter;
}

Iter_Change::Iter_Change(sr_change_iter_t *iter) {_iter = iter;}
Iter_Change::~Iter_Change() {if (_iter) sr_free_change_iter(_iter);}