//
// Created by j0sh on 6/26/16.
//

#include "type.h"


type *T_BASE = new type();
type *T_NUMERIC = new type(T_BASE, "numeric");
type *T_INT = new type(T_NUMERIC, "int");
type *T_FUNCTION = new type(T_BASE, "function");
