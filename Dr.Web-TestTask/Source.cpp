#include <iostream>
#include <vector>

template<class Key, class Value>
class dictionary {
public:
	virtual ~dictionary() = default;

	virtual const Value& get(const Key& key) const = 0;
	virtual void set(const Key& key, const Value& value) = 0;
	virtual void is_set(const Key& key) const = 0;
};

template<class Key>
class not_found_exception : public std::exception {
public:
	virtual void get_key(Key) noexcept = 0;
};

template<class Key>
class exeption_interface : public not_found_exception<Key> {
public:
	void get_key(Key key)
	{
		std::cout << "not_found_exeption: Key" << key << std::endl;
	}

};

template<class Key, class Value>
class element {
public:
	Key key;
	Value value;
};

template<class Key, class Value>
class dictionary_container : public dictionary<Key, Value> {
private:
	std::vector <element<Key, Value>> container;
	exeption_interface<Key> *except;
public:
	dictionary_container(std::vector<element<Key, Value>> new_container)
	{
		for (element<Key, Value> n : new_container) {
			container.push_back(n);
		}
		except = new exeption_interface<Key>();
	}

	const Value& get(const Key& key) const {

		Value temp;
		int i = 0;
		is_set(key);
		for (element<Key, Value> n : container) {
			if (key == n.key) {
				temp = n.value;
				break;
			}
			i++;
		}
		return temp;
	}
	
	void set(const Key& key, const Value& value) {
		int i = 0;
		is_set(key);
		for (element<Key, Value> n : container) {
			if (key == n.key) {
				n.value = value;
				break;
			}
			i++;
		}
	}
	
	void is_set(const Key& key) const {
		try {

			for (element<Key, Value> n : container)
				if (key == n.key)
					if (n.value == '\0')
						throw exeption_interface<Key>();
		}
		catch (std::exception& ex)
		{
			except->get_key(key);
		}
	}
};