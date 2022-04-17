#pragma once
#include<concepts>
#include<array>
#include<avr/eeprom.h>

namespace avr{
	template<typename T>
	struct eeprom_ref{
	private:
		T* const ptr;
	public:
		explicit eeprom_ref(T* const p): ptr(p) {}
		operator const T () const ;
		void operator=(const T& n){
			static_assert("Not implemented yet");	
		}
	};

	template<typename T> concept WORD_LIKE = (sizeof(T) == sizeof(uint16_t));
	template<typename T>
		requires WORD_LIKE<T>
	eeprom_ref<T>::operator const T () const {
		union nn{
			uint16_t nat;
			const T  ret;

			nn() {}
		} U;
		U.nat = eeprom_read_word( static_cast<const uint16_t*>(static_cast<const void*>(ptr)) );	
		return U.ret;
	}

	template<typename T> concept Constant = std::is_same_v<T, std::add_const_t<T>>;

	//Every instance should be placed to .eeprom section!!!!!!!!!!!
	template<Constant T, unsigned char S> //Constant since no write operation is implemented
	struct eeprom_array{
	private:
		std::array<T, S> arr;
	public:
		template<typename... U>
		constexpr eeprom_array(U... i): arr{i...} {}


		eeprom_ref<const T> operator[](unsigned char offset) const {
			return eeprom_ref<T> {&arr[offset]};
		}

		eeprom_ref<T> operator[](unsigned char offset) {
			return eeprom_ref<T> {&arr[offset]};
		}

		constexpr auto size() const noexcept { return arr.size(); }
		using value_type=T;
	};

	template <class W, class... U> eeprom_array(W, U...) -> eeprom_array<const W, 1 + sizeof...(U)>;
}
