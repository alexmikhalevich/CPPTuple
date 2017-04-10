#pragma once

#include <iostream>
#include <list>
#include <string>
#include <map>
#include <memory>
#include <vector>

class IType {
	public:
		virtual void* value() = 0;
		virtual const std::string& get_type() const = 0;
		virtual ~IType() {}
};

template<class T>
class CType : public IType {
	private:
		T m_val;
		std::string m_type_id;
	public:
		CType(const std::string& type) : m_type_id(type) {}
		virtual void* value() {
			return reinterpret_cast<void*>(&m_val);
		}
		virtual const std::string& get_type() const {
			return m_type_id;
		}
		virtual ~CType() {}
};

class IAbstractTypeCreator {
	public:
		virtual std::shared_ptr<IType> create(const std::string& type_id) = 0;
		virtual ~IAbstractTypeCreator() {}
};

template<class T>
class CTypeCreator : public IAbstractTypeCreator {
	public:
		virtual std::shared_ptr<IType> create(const std::string& type_id) {
			return std::shared_ptr<CType<T>>(new CType<T>(type_id));
		}
};

class CTypeFactory {
	public:
		typedef std::map<std::string, std::shared_ptr<IAbstractTypeCreator>> types_map;
		static types_map m_types;

		template<class T>
		static void register_type(const std::string& type) {
			auto it = m_types.find(type);
			if (it == m_types.end()) {
				m_types[type] = std::shared_ptr<IAbstractTypeCreator>(new CTypeCreator<T>());
			}
		}

		static std::shared_ptr<IType> create(const std::string& type) {
			auto it = m_types.find(type);
			if (it == m_types.end()) {
				return nullptr;
			}
			return it->second->create(type);
		}

		static std::string get_supported() {
			std::string res = "";
			for (auto elem : m_types) {
				res += elem.first + "\n";
			}
			return res;
		}
};

class CTuple {
	private:
		std::vector<std::shared_ptr<IType>> m_types;
	public:
		explicit CTuple(const std::list<std::string>& types);
		void* operator[](int index);
		std::string type(int index) const;
		~CTuple() {}
};
