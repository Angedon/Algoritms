#include<iostream>
#include<vector>
#include<string>
using namespace std;

template <class K, class V>
class Couple
{
public:
	K key;
	V value;
	bool exist;
	bool deleted;
	Couple(K key, V value)
	{
		this->key = key;
		this->value = value;
		exist = true;
		deleted = false;
	}
	K getKey()
	{
		return key;
	}
	V getValue()
	{
		return value;
	}
	void setKey(K key)
	{
		this->key = key;
	}
	void setValue(V value)
	{
		this->value = value;
	}
};

template<class K, class V>
class HashMap
{
	friend class Iterator;
private:
	vector<vector<Couple<K, V>*> > arrayA;
	vector<K> keys;
	vector<V> values;
	int countOfElem;
	int adressKey;
	int adressInnerKey;
	long long sizeT;
	char type;
public:
	HashMap(char type)
	{
		this->type = type;
		sizeT = 32770;
		countOfElem = 0;
		adressKey = 0;
		adressInnerKey = 0;
		arrayA.resize(sizeT + 1);
		//arrayA[sizeT].push_back(new Couple());
	}
	long long getSize() { return sizeT; }
	Couple<K, V>* get(K key)
	{
		int index = hash(key, sizeT);
		int sizeA = arrayA[index].size();
		for (int i = 0; i < sizeA; ++i)
		{
			if (arrayA[index][i]->key == key) return arrayA[index][i];
		}
		return NULL;
	}
	char getType()
	{
		return type;
	}
	int getSizeKeys()
	{
		return keys.size();
	}
	K getKey(int index)
	{
		return keys[index];
	}
	vector<Couple<K, V>*> getElemOfArray(int index)
	{
		return arrayA[index];
	}

	void add(K key, V value)
	{
		keys.push_back(key);
		values.push_back(value);
		int index = hash(key, sizeT);
		int position = -1;
		int sizeA = arrayA[index].size();
		for (int i = 0; i < sizeA; ++i)
			if (arrayA[index][i]->key == key) position = i;
		if (position != -1) countOfElem++;
		(position != -1 ? arrayA[index][position]->value = value : arrayA[index].push_back(new Couple<K, V>(key, value)));


		if ((countOfElem / arrayA.size() * 100) >= 70) rehash();
	}
	void remove()
	{

	}
	size_t operator ()(K key)
	{
		return sizeof(K);
	}
	size_t hash(K key, long long sizet)
	{
		std::hash<K> hasher;
		return hasher(key) % sizet;
	}
	vector<vector<Couple<K, V>*> > rehash()
	{
		if (sizeT * 2 < sizeof(long long))
		{
			vector<vector<Couple<K, V>*>> newArray(2 * sizeT + 1);
			//for (int i = 0; i < 2 * sizeT + 1; ++i) newArray[i] = NULL;
			int keySize = keys.size();
			for (int i = 0; i < keySize; ++i)
			{
				newArray[this->hash(keys[i], 2 * sizeT)] = arrayA[this->hash(keys[i], sizeT)];
			}
			arrayA = newArray;
			sizeT *= 2;
			//arrayA[sizeT].push_back(NULL);
		}
		return this->arrayA;
	}
	Couple<K, V>* first()
	{
		if (this->keys.size() != 0)
		{
			int i = 0;
			while (i < sizeT && arrayA[i].size() == 0) i++;
			return this->arrayA[i][0];
		}
		else return NULL;
	}
	Couple<K, V>* next(Couple<K, V>* couple)
	{
		int index = this->hash(couple->getKey(), sizeT);
		int position = -1;
		int sizeA = this->arrayA[index].size();
		for (int i = 0; i < sizeA; ++i)
		{
			if (this->arrayA[index][i]->value == couple->value)
			{
				position = i;
			}
		}
		if (position == -1)
		{
			return NULL;
		}
		else if(position >= sizeA - 1)
		{
			index++;
			while (index < sizeT && this->arrayA[index].size() == 0) index++;
			if (index < sizeT)
			{
				cout << this->arrayA[index][0]->value << endl;
				return this->arrayA[index][0];
			}
			else
			{
				index = 0;
				while (index < sizeT && this->arrayA[index].size() == 0) index++;
				cout << this->arrayA[index][0]->value << endl;
				return this->arrayA[index][0];
			}
		}
		else
		{
			cout << this->arrayA[index][position+1]->value << endl;
			return this->arrayA[index][position+1];
		}


		/*if (keys.size() != 0 && adressKey < sizeT && adressInnerKey < arrayA[adressKey].size())
		{
			cout << adressKey << endl;
			if (arrayA[adressKey][0] != NULL)
				return arrayA[adressKey][adressInnerKey++];
		}
		else if (keys.size() != 0) {
			adressKey++;
			while (adressKey < sizeT && arrayA[adressKey].size() == 0) adressKey++;
			if (adressKey >= sizeT)
			{
				adressKey = 0;
				while (adressKey < sizeT && arrayA[adressKey].size() == 0) adressKey++;
			}
			cout << adressKey << endl;
			if (arrayA[adressKey][0] != NULL)
				return arrayA[adressKey][0];
			adressInnerKey = 1;
		}
		else
		{
			cout << "null" << endl;
			return NULL;
		}*/
	}



	class Iterator
	{
		friend class HashTable;
	private:
		Couple<K, V>* current;
		HashMap<K, V>* map;
		int indexKey;
		int indexCouple;
	public:
		Iterator(HashMap<K, V>* mapA, Couple<K, V>* cur)
		{
			current = cur;
			map = mapA;
			indexKey = 0;
			indexCouple = 0;
		}
		Iterator(HashMap<K, V>* mapA)
		{
			current = NULL;
			map = mapA;
			indexKey = 0;
			indexCouple = 0;
		}
		Iterator(Iterator* iter)
		{
			this->current = iter->current;
			this->map = iter->map;
			this->indexKey = iter->indexKey;
			this->indexCouple = iter->indexCouple;
		}
		HashMap<K, V>* getMap()
		{
			return map;
		}
		Couple<K, V>* getCurrent()
		{
			return current;
		}
		void setCurrent(Couple<K, V>* couple)
		{
			current = couple;
		}
		V getValue()
		{
			return current->value;
		}
		//Couple* getCurrent()
		//{
		//	return current;
		//}
		//Iterator& operator += (int count)
		//{
		//	while (count != 0)
		//	{
		//		this->current = this->map->next();
		//		count--;
		//	}
		//	return this;
		//}
		void foo(Couple<K, V>* couple)
		{
			cout << couple->value << endl;
		}
		//Iterator& operator ++ (int trash)
		//{
		//	//Iterator iter(*this);
		//	cout << this->current->getValue() << endl;
		//	this->current = this->map->next(this->current);
		//	foo(this->current);
		//	//cout << this->current->getValue() << endl;
		//	return *this;
		//}
		Iterator& operator ++ ()
		{
			//Iterator iter(*this);
			cout << this->current->value << endl;
			this->current = this->map->next(this->current);
			//cout << this->current->getValue() << endl;
			//return this;
		}
		/*Iterator operator ++ ()
		{
			current = map->next();
			return this;
		}*/
		bool operator != (Iterator* it2)
		{
			if (it2->current != this->current) return 1;
			else return 0;
		}
		Iterator* begin()
		{
			//cout << map->sizeT << endl;
			if (map->keys.size() != 0)
			{
				Iterator* it = new Iterator(map, this->map->first());
				//it->value = map->arrayA[this->indexKey][0]->value;
				return it;
			}
			else return NULL;
		}
		Iterator* end()
		{
			if (map->getSizeKeys() != 0)
			{
				Iterator* it = new Iterator(map, this->map->arrayA[this->map->sizeT][0]);
				return it;
			}
			else return NULL;
		}
		void print()
		{
			cout << current->value << endl;
		}
	};
};


int main()
{
	HashMap<int, string>* map = new HashMap<int, string>('I');
	map->add(1, "Mike");
	map->add(1, "Tom");
	map->add(2, "Nil");
	/*cout << map->getElemOfArray(0).size() << endl;
	for (long long i = 0; i < map->getSize(); ++i) if (map->getElemOfArray(i).size() != 0) cout << 1 << endl;*/

	//cout << map->get(1)->value;

	HashMap<int, string>::Iterator* iT = new HashMap<int, string>::Iterator(map);
	HashMap<int, string>::Iterator* it = iT->begin();
	cout << it->getValue() << endl;
	++it;
	it->getCurrent();
}
