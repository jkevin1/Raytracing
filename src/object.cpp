#include "object.h"

Object::Object(const Material& mat, Object* next) : mat(mat) {
	this->next = next;
}

Object::~Object() {
	//Empty destructor, virtual in case subclasses have to free memory
}
