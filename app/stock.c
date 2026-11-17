int modificarProducto(tNodoArbol * pArbol, int pCodigo, tProducto pNuevosDatos){
    int modificado = 0;
    tNodoArbol * nodo = buscarProducto(pArbol, pCodigo);
    if(nodo != NULL && validarProducto(pNuevosDatos) == 1){
        nodo->datos = pNuevosDatos;
        nodo->datos.codigo = pCodigo;
        modificado = 1;
    }
    return modificado;
}