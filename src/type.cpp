// (c) Copyright 2016 Josh Wright
#include "type.h"

type *T_BASE = new type();
type *T_NUMERIC = new type(T_BASE, "numeric");
type *T_INT = new type(T_NUMERIC, "int");
type *T_DECIMAL = new type(T_NUMERIC, "decimal");
type *T_SEQUENCE = new type(T_BASE, "sequence");
type *T_VECTOR = new type(T_BASE, "sequence");
type *T_LIST = new type(T_BASE, "sequence");
type *T_FUNCTION = new type(T_BASE, "function");
