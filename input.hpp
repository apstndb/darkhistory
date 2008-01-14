#include <string>
class KanaSet;
class Input {

	std::wstring* buffer;
	std::wstring* kana;
	bool lock_;
	public:
	Input()
	{
	}
	void backspace();
	void clear();

	void operator()(int c);
	void regen_kana(KanaSet* set);
	const std::wstring& get_kana() const
	{
		return *kana;
	};
	inline const size_t size() const;

};

