#pragma once
#include<memory>
#include<string>


	class Json {

		//life cycle management 
	public:
		// Destructor
		/*~Json();
		Json(const Json&) = delete;
		Json(Json&&) = delete;
		Json& operator = (const Json&) = delete;
		Json& operator = (Json&&) = delete;*/


	public:
		/**
		* default constructor
		*/
		Json();

		/**
		* this constructs a json object consists of the "null" literal
		*  @param[in] null
		* This is the object to wrap in JSON.
		*/ 
		Json(nullptr_t);



		/**
		* this constructs a json object consists of the "boolean" value
		*  @param[boolean] null
		* This is the object to wrap in JSON.
		*/
		Json(bool value);

		/**
		* encodes the JSON object into a its string rendering
		*/
		std::string toString() const;

		/**
		* Converts a JSON string into an object.
		*/
		static Json parse(const std::string& format);

	private:
		/**
		* this is the type of struct that contains the private properties of the instance.
		* It is defined in the implementation and declared here to ensure that it is scoped inside the class.
		*/
		struct Impl;

		/**
		* This contains the private properties of the instance.
		*/
		std::unique_ptr<struct Impl> impl_;
	};