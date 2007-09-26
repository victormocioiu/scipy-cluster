/**
 * cluster_wrap.c
 *
 * Author: Damian Eads
 * Date:   September 22, 2007
 *
 * Copyright (c) 2007, Damian Eads
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *   - Redistributions of source code must retain the above
 *     copyright notice, this list of conditions and the
 *     following disclaimer.
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer
 *     in the documentation and/or other materials provided with the
 *     distribution.
 *   - Neither the name of the author nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "cluster.h"
#include "Python.h"
#include <numpy/arrayobject.h>
#include <stdio.h>

PyObject *chopmin_ns_ij_wrapper(PyObject *self, PyObject *args);
PyObject *chopmin_ns_i_wrapper(PyObject *self, PyObject *args);
PyObject *chopmins_wrapper(PyObject *self, PyObject *args);

extern PyObject *cluster_wrapper(PyObject *self, PyObject *args) {
  int method, n;
  PyArrayObject *dm, *Z;
  distfunc *df;
  if (!PyArg_ParseTuple(args, "O!O!ii",
			&PyArray_Type, &dm,
			&PyArray_Type, &Z,
			&n,
			&method)) {
    return 0;
  }
  else {
    switch (method) {
    case CPY_LINKAGE_SINGLE:
      df = dist_single;
      break;
    case CPY_LINKAGE_COMPLETE:
      df = dist_complete;
      break;
    default:
      /** Report an error. */
      df = 0;
      break;
    }
    linkage((double*)dm->data, (double*)Z->data, n, 1, df);
  }
  return Py_BuildValue("d", 0.0);
}

extern PyObject *chopmin_ns_ij_wrapper(PyObject *self, PyObject *args) {
  int mini, minj, n;
  PyArrayObject *row;
  if (!PyArg_ParseTuple(args, "O!iii",
			&PyArray_Type, &row,
			&mini,
			&minj,
			&n)) {
    return 0;
  }
  chopmins_ns_ij((double*)row->data, mini, minj, n);
  return Py_BuildValue("d", 0.0);
}

extern PyObject *chopmin_ns_i_wrapper(PyObject *self, PyObject *args) {
  int mini, n;
  PyArrayObject *row;
  if (!PyArg_ParseTuple(args, "O!ii",
			&PyArray_Type, &row,
			&mini,
			&n)) {
    return 0;
  }
  chopmins_ns_i((double*)row->data, mini, n);
  return Py_BuildValue("d", 0.0);
}

extern PyObject *chopmins_wrapper(PyObject *self, PyObject *args) {
  int mini, minj, n;
  PyArrayObject *row;
  if (!PyArg_ParseTuple(args, "O!iii",
			&PyArray_Type, &row,
			&mini,
			&minj,
			&n)) {
    return 0;
  }
  chopmins((int*)row->data, mini, minj, n);
  return Py_BuildValue("d", 0.0);
}

extern PyObject *to_squareform_from_vector(PyObject *self, PyObject *args) {
  PyArrayObject *_M, *_v;
  int n;
  double *v, *M;
  if (!PyArg_ParseTuple(args, "O!O!",
			&PyArray_Type, &_M,
			&PyArray_Type, &_v)) {
    return 0;
  }
  else {
    M = (double*)_M->data;
    v = (double*)_v->data;
    n = _M->dimensions[0];
    dist_to_squareform_from_vector(M, v, n);
  }
  return Py_BuildValue("d", 0.0);
}

extern PyObject *to_vector_from_squareform(PyObject *self, PyObject *args) {
  PyArrayObject *_M, *_v;
  int n;
  double *v, *M;
  if (!PyArg_ParseTuple(args, "O!O!",
			&PyArray_Type, &_M,
			&PyArray_Type, &_v)) {
    return 0;
  }
  else {
    M = (double*)_M->data;
    v = (double*)_v->data;
    n = _M->dimensions[0];
    dist_to_vector_from_squareform(M, v, n);
  }
  return Py_BuildValue("d", 0.0);
}

extern PyObject *pdist_euclidean_wrap(PyObject *self, PyObject *args) {
  PyArrayObject *_X, *_dm;
  int m, n;
  double *dm, *X;
  if (!PyArg_ParseTuple(args, "O!O!",
			&PyArray_Type, &_X,
			&PyArray_Type, &_dm)) {
    return 0;
  }
  else {
    X = (double*)_X->data;
    dm = (double*)_dm->data;
    m = _X->dimensions[0];
    n = _X->dimensions[1];
    
    pdist_euclidean(X, dm, m, n);
  }
  return Py_BuildValue("d", 0.0);
}

extern PyObject *pdist_city_block_wrap(PyObject *self, PyObject *args) {
  PyArrayObject *_X, *_dm;
  int m, n;
  double *dm, *X;
  if (!PyArg_ParseTuple(args, "O!O!",
			&PyArray_Type, &_X,
			&PyArray_Type, &_dm)) {
    return 0;
  }
  else {
    X = (double*)_X->data;
    dm = (double*)_dm->data;
    m = _X->dimensions[0];
    n = _X->dimensions[1];
    
    pdist_city_block(X, dm, m, n);
  }
  return Py_BuildValue("d", 0.0);
}

extern PyObject *pdist_minkowski_wrap(PyObject *self, PyObject *args) {
  PyArrayObject *_X, *_dm;
  int m, n;
  double *dm, *X;
  double p;
  if (!PyArg_ParseTuple(args, "O!O!d",
			&PyArray_Type, &_X,
			&PyArray_Type, &_dm,
			&p)) {
    return 0;
  }
  else {
    X = (double*)_X->data;
    dm = (double*)_dm->data;
    m = _X->dimensions[0];
    n = _X->dimensions[1];
    
    pdist_minkowski(X, dm, m, n, p);
  }
  return Py_BuildValue("d", 0.0);
}


static PyMethodDef _clusterWrapMethods[] = {
  {"cluster_impl", cluster_wrapper, METH_VARARGS},
  {"chopmins_ns_ij", chopmin_ns_ij_wrapper, METH_VARARGS},
  {"chopmins_ns_i", chopmin_ns_i_wrapper, METH_VARARGS},
  {"chopmins", chopmins_wrapper, METH_VARARGS},
  {"pdist_euclidean_wrap", pdist_euclidean_wrap, METH_VARARGS},
  {"pdist_city_block_wrap", pdist_city_block_wrap, METH_VARARGS},
  {"pdist_minkowski_wrap", pdist_minkowski_wrap, METH_VARARGS},
  {"to_squareform_from_vector", to_squareform_from_vector, METH_VARARGS},
  {"to_vector_from_squareform", to_vector_from_squareform, METH_VARARGS},
  {NULL, NULL}     /* Sentinel - marks the end of this structure */
};

void init_cluster_wrap()  {
  (void) Py_InitModule("_cluster_wrap", _clusterWrapMethods);
  import_array();  // Must be present for NumPy.  Called first after above line.
}
