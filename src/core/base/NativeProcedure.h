#ifndef SHAKA_CORE_BASE_NATIVEPROCEDURE_H
#define SHAKA_CORE_BASE_NATIVEPROCEDURE_H

#include "core/base/IProcedure.h"
#include "core/base/Environment.h"
#include "core/base/Data.h"

#include <functional>
#include <typeinfo>
#include <vector>

namespace shaka {

class NativeProcedure : public IProcedure {
public:
    using Key = shaka::Symbol;
    using Value = NodePtr;
    //using IEnvPtr = std::shared_ptr<shaka::Environment>;
    //using Value = std::shared_ptr<IDataNode<Data>>;
    using Args = std::vector<Value>;
    using Function = std::function<Args(Args, EnvPtr)>;


	NativeProcedure(
        Function	   func,
        std::size_t    fixed_arity, 
        bool           variable_arity = false) :
		func(func),
		fixed_arity(fixed_arity),
		variable_arity(variable_arity) {}
	
	
	virtual Args call(Args v, EnvPtr env) {
		if (v.size() > fixed_arity && !variable_arity) {
			throw std::runtime_error("NativeProcedure.call: incorrect number of arguments");
		}
		else {

			return func(v, env);
		}
	
	}
	// I don't think this really evaluates a procedure call
	/*shaka::Evaluator<Data, Key, Value> evaluator(current_env, body_root);
	
	// What is the machine that will be used to execute the actual procedure call
	// here. This seems to do nothing. Eval_Expression does not have the ability
	// to evaluate a procedure call. Is it supposed to be Eval_Proc_Call's job?
	auto result = evaluator.evaluate(shaka::Eval_Expression<Data, Key, Value>());

	auto return_values = std::vector<std::shared_ptr<IDataNode<Data>>>();

	return_values.push_back(result);

	return return_values;*/

	virtual std::size_t get_fixed_arity() const {
		return fixed_arity;
	}

	virtual bool is_variable_arity() const {
		return variable_arity;
	}

    friend bool operator== (const NativeProcedure&, const NativeProcedure&);
    friend bool operator!= (const NativeProcedure&, const NativeProcedure&);
    friend std::ostream& operator<< (std::ostream&, const NativeProcedure&);
private:
	/*std::shared_ptr<IEnvironment<Key, Data>> parent_env;
	std::shared_ptr<IEnvironment<Key, Data>> current_env;
	std::shared_ptr<IDataNode<Data>> body_root;*/
	Function func;
	std::size_t fixed_arity;
	bool variable_arity;
};

bool operator== (const shaka::NativeProcedure& lhs,
                 const shaka::NativeProcedure& rhs) {
    if (lhs.func.target_type() == rhs.func.target_type()) {
        return &lhs.func == &rhs.func;
    }
    else{
        return false;
    }
}

bool operator!= (const shaka::NativeProcedure& lhs,
                 const shaka::NativeProcedure& rhs) {
    return !operator==(lhs, rhs);
}

std::ostream& operator<< (std::ostream& lhs, const shaka::NativeProcedure& rhs) {
    // Turning off rhs unused warning
    static_cast<void>(rhs);
    lhs << "#<procedure>";
    return lhs;
}

}// namespace shaka

#endif // SHAKA_CORE_BASE_NATIVEPROCEDURE_H
