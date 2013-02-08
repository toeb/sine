#pragma once

#include <core.collection/Operations.h>
#include <core.collection/Operators.h>
#include <core.collection/Enumerable.h>
#include <core.collection/containers/Array.h>
#include <core.collection/containers/LinkedList.h>
#include <core.collection/containers/Set.h>

//specialization
#include <core.collection/specialization/array.h>  //this takes long to compile.... maybe it should not be on by default
#include <core.collection/specialization/stdcontainer.h>
#include <core.collection/specialization/dslib.h>
#include <core.collection/specialization/linkedlist/Enumerator.h>
#include <core.collection/specialization/linkedlist/AddItem.h>
#include <core.collection/specialization/linkedlist/RemoveItem.h>
