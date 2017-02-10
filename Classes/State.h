#pragma once

template<class Type>
class State
{
public:
	virtual ~State() {}
	virtual void enter(Type*) = 0;
	virtual void execute(Type*) = 0;
	virtual void exit(Type*) = 0;
	virtual bool onMessage(Type*, const Telegram&) = 0;
};