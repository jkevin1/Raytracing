#include "object.h"

Object::Object(const Material& mat) : mat(mat) {
	next = nullptr;
}

Object::~Object() {
	delete next;
}
