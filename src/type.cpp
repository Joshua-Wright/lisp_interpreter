//
// Created by j0sh on 6/26/16.
//

#include "type.h"


const type *T_BASE = new type();
const type *T_NUMERIC = new type(T_BASE, "numeric");
const type *T_INT = new type(T_NUMERIC, "int");
const type *T_FUNCTION = new type(T_BASE, "function");
