#ifndef KANASET_HPP
#define KANASET_HPP
#include <string>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/key_extractors.hpp>
#include <boost/multi_index/random_access_index.hpp>
using namespace boost::multi_index;
struct KanaYomi {
	std::wstring kana;
	std::wstring yomi;
	KanaYomi()
		: kana(),yomi()
	{
	}
	KanaYomi(std::wstring& kana_, std::wstring& yomi_)
		: kana(kana_),yomi(yomi_)
	{
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
	typedef multi_index_container<
		KanaYomi,
		indexed_by<
			random_access<tag<by_random> >,
		ordered_unique<tag<by_yomi>,identity<KanaYomi>,yomi_comparator >			>
			> kanaset_set_t;
	kanaset_set_t kanaset;
	typedef kanaset_set_t::index<by_yomi>::type kanaset_yomi_index;
	typedef kanaset_set_t::index<by_random>::type kanaset_random_index;

	//inline KanaYomi random();
	std::wstring to_kana(const std::wstring&);
	KanaSet(const char*); 
};
#endif // KANASET_HPP
