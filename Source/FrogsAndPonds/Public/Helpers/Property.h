// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

template <typename T> 
class FROGSANDPONDS_API Property
{
// Lifecycle
public:
	Property();
	Property(const TFunction<void(T OldValue, T NewValue)>& OnChange);


// Operators
public:
	operator T() const;
	void operator=(const T& NewValue);
	T operator->() const;

	
// Variables
private:
	T Value;
	TFunction<void(T OldValue, T NewValue)> OnChangeFunction;
};


// Implementations
template <typename T>
Property<T>::Property()
{
	OnChangeFunction = nullptr;
}

template <typename T>
Property<T>::Property(const TFunction<void(T OldValue, T NewValue)>& OnChange)
{
	OnChangeFunction = OnChange;
}

template <typename T>
Property<T>::operator T() const
{
	return Value;
}

template <typename T>
void Property<T>::operator=(const T& NewValue)
{
	if (Value == NewValue) return;
	T OldValue = Value;
	Value = NewValue;
	OnChangeFunction(OldValue, NewValue);	
}

template <typename T>
T Property<T>::operator->() const
{
	static_assert(std::is_pointer_v<T>, "operator-> can only be used when T is a pointer.");
	return Value;
}
