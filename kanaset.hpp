#ifndef KANASET_HPP
#define KANASET_HPP
#include <string>
#include <vector>
struct KanaYomi {
	std::wstring kana;
	std::wstring yomi;
	KanaYomi()
		: kana(),yomi()
	{
	}
	explicit KanaYomi(std::wstring& kana_, std::wstring& yomi_)
		: kana(kana_),yomi(yomi_)
	{
	}
	bool operator==(const std::wstring& other) const {
		return yomi == other; 
	}
	bool operator<(const KanaYomi& other) const {
		return yomi < other.yomi; 
	}
};
struct by_kana {};
struct by_yomi {};
struct by_fifo {};
struct by_random {};
struct kana_comparator {
	bool operator()(const KanaYomi& lhs, const KanaYomi& rhs) const {
		return lhs.kana < rhs.kana;
	}
	bool operator()(const KanaYomi& lhs, const std::wstring& rhs) const {
		return lhs.kana < rhs;
	}
	bool operator()(const std::wstring& lhs, const KanaYomi& rhs) const {
		return lhs < rhs.kana;
	}
};
struct yomi_comparator {
	bool operator()(const KanaYomi& lhs, const KanaYomi& rhs) const {
		return lhs.yomi < rhs.yomi;
	}
	bool operator()(const KanaYomi& lhs, const std::wstring& rhs) const {
		return lhs.yomi < rhs;
	}
	bool operator()(const std::wstring& lhs, const KanaYomi& rhs) const {
		return lhs < rhs.yomi;
	}
};
class KanaSet {
	unsigned int maxchar;
	inline void push(const KanaYomi& entry) {
		kanaset.push_back(entry);
		unsigned i=entry.yomi.size();
		maxchar=(maxchar<i)?i:maxchar;
	};
	public:
	typedef std::vector<KanaYomi> kanaset_set_t;
	kanaset_set_t kanaset;

	std::wstring to_kana(const std::wstring&);
	KanaSet(const char*); 
};
#endif // KANASET_HPP
