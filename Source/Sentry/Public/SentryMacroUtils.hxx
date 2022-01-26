#pragma once

#define SENTRY_SETTER(ParentStruct, FieldType, Field)   \
	ParentStruct& Set##Field##(const FieldType& Value_) \
	{                                                   \
		Field = Value_;                                 \
		return *this;                                   \
	}                                                   \
	ParentStruct& Set##Field##(FieldType && Value_)     \
	{                                                   \
		Field = std::move(Value_);                      \
		return *this;                                   \
	}

#define SENTRY_SETTER_MAP(ParentStruct, KeyType, ValueType, Field)     \
	ParentStruct& Set##Field##(const TMap<KeyType, ValueType>& Value_) \
	{                                                                  \
		Field = Value_;                                                \
		return *this;                                                  \
	}                                                                  \
	ParentStruct& Set##Field##(TMap<KeyType, ValueType> && Value_)     \
	{                                                                  \
		Field = std::move(Value_);                                     \
		return *this;                                                  \
	}                                                                  \
	ParentStruct& Add##Field##(const TMap<KeyType, ValueType>& Value_) \
	{                                                                  \
		Field.Append(Value_);                                          \
		return *this;                                                  \
	}                                                                  \
	ParentStruct& Add##Field##(TMap<KeyType, ValueType> && Value_)     \
	{                                                                  \
		Field.Append(std::move(Value_));                               \
		return *this;                                                  \
	}