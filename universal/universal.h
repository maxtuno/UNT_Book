///////////////////////////////////////////////////////////////////////////////
//        copyright (c) 2012-2017 Oscar Riveros. all rights reserved.        //
//                           oscar.riveros@peqnp.com                         //
//                                                                           //
//    without any restriction, Oscar Riveros reserved rights, patents and    //
//  commercialization of this knowledge or derived directly from this work.  //
///////////////////////////////////////////////////////////////////////////////

#ifndef UNIVERSAL_CODE_H
#define UNIVERSAL_CODE_H

typedef struct {
    char *data;
} universal;

universal *universal_new();

universal *universal_from_string(char *u);

char *universal_to_string(universal *u);

universal *universal_add(universal *u, universal *v);

universal *universal_multiply(universal *u, universal *v);

#endif //UNIVERSAL_CODE_H
