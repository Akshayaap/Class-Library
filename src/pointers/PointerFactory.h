#pragma once



namespace pointers {

	class Factory;
	template<class T>
	class Pointer {
	private:
		const T* ptr;
		Factory* factory;
		Pointer(Factory* factory, T* ptr);
	public:
		
		Pointer(const Pointer&);
		~Pointer();


	public:
		T GetTarget()const;
		const T const* Get()const;
		Pointer* operator &()=delete;
		Pointer& operator = (const Pointer&);
		Pointer& operator = (void*)=delete;
		static Pointer<T> const NullPtr = Pointer();
		T operator*(); //returns only rvalue

	};

	class Factory {

	private:
		std::unordered_map<unsigned long long,int> map;
		static constexpr Factory *factory=nullptr;
		Factory();
	public:
		
		Factory& operator =(Factory&)=delete;
		Factory(const Factory&)=delete;
		~Factory();

		template<class T>
		Pointer<T> MakePtr(T*);
		Factory* operator &() = delete;
		static Factory& getInstance();

		void AddRef(unsigned long long index);
		template<class T>
		void DecRef(unsigned long long index);
	};

}

