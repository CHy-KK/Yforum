#pragma once
#ifndef DATA_H
#define DATA_H
#include "user.h"

typedef vector<Commentptr>::iterator iteratorc;
typedef vector<Postptr>::iterator iteratorp;
typedef map<PostType, vector<Postptr> >::iterator iteratorpp;
typedef vector<Userptr>::iterator iteratoru;
typedef vector<Commentptr>* Commentlistptr;
typedef vector<Commentptr> Commentlist;
enum State { initial, log_in, Register, postview, typechoose, inpost, end_s };
#endif // DATA_H
