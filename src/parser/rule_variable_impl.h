#ifndef RULE_VARIABLE_IMPL_H
#define RULE_VARIABLE_IMPL_H

#include "rule_variable.h"

namespace shaka {
namespace parser {
namespace rule {

template <typename T>
bool variable(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
	Token var_tok = in.peek();
	
	if (var_tok.type == Token::Type::IDENTIFIER) {
		//Take string and create DataNode that holds a shaka::Symbol
		//interm temporarily holds a value
		in.get();
		interm = var_tok.get_string();
		//Use interm to push the DataNode onto tree
		root->push_child(Symbol(interm));
		return true;
	}

	return false;
	
}

}
}
}

#endif 