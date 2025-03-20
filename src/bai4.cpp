#pragma once
#include<bits/stdc++.h>
#include "sol4.h"

LinkedList* LinkedList::createEvenList(){
    LinkedList* N_List = new() LinkedList ;
    N_List->head = this->head->next ;
    Node * beg = N_List->head ;
    while ( true ){
        Node * x = beg->next ;
        x = x->next ;
        if ( x == nullptr ){
            N_List->tail = beg ;
            break ;
        }
        else beg->next = x ;
    }
    return N_List ;
}
