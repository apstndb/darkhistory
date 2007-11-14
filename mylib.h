#include <vector>
#include <map>
#include <string>
#include <utility>
//#include <iostream>
//#include <boost/shared_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/key_extractors.hpp>
#include <boost/multi_index/sequenced_index.hpp>
using std::wstring;
using std::multimap;
using std::vector;
using std::pair;
using namespace boost::multi_index;
struct KanaYomi {
//	public:
	wstring kana;
	wstring yomi;
//	wstring& getKana() {return kana;}
//	wstring& getYomi() {return yomi;}
	bool operator<(const KanaYomi& r) const {
		return yomi < r.yomi;
	}
	KanaYomi(wstring _kana, wstring _yomi):
	kana(_kana),yomi(_yomi)
	{
	}
};
struct by_kana {};
struct by_yomi {};
struct by_fifo {};
//typedef boost::shared_ptr<const KanaYomi> KanaYomiPtr;
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
struct KanaSet {
	typedef multi_index_container<
		KanaYomi,
		indexed_by<
			sequenced<tag<by_fifo> >,
		ordered_unique<tag<by_yomi>,identity<KanaYomi>,yomi_comparator >,
		ordered_non_unique<
			tag<by_kana>,
		member<KanaYomi, wstring, &KanaYomi::kana> >
			>
			> kanaset_set_t;
	unsigned int maxchar;
/*	typedef multi_index_container<
		KanaYomi,
		indexed_by<
			sequenced<tag<by_fifo> >,
		ordered_unique<tag<by_yomi>,identity<KanaYomi>,yomi_comparator >,
		ordered_non_unique<
			tag<by_kana>,
//		mem_fun<KanaYomi, wstring&, &KanaYomi::getKana> >
		member<KanaYomi, wstring, &KanaYomi::kana> >
			>
			> kanaset_set_t;*/
	kanaset_set_t kanaset;
//	public:
	typedef kanaset_set_t::index<by_kana>::type kanaset_kana_index;
	typedef kanaset_set_t::index<by_yomi>::type kanaset_yomi_index;
	typedef kanaset_set_t::index<by_fifo>::type kanaset_fifo_index;
	//KanaYomi searchByYomi(const wstring &yomi);
	//      vector<KanaYomi> searchByKana(const wstring &Kana);

	wstring to_kana(const wstring&);
	inline void push(const KanaYomi& entry) {
		kanaset.push_back(entry);
		unsigned i=entry.yomi.size();
		maxchar=(maxchar<i)?i:maxchar;
	};
	//inline void push(const KanaYomi& entry) { kanaset.push_back(entry);};
	//	KanaYomi front() const;
	//	void pop();
};

vector<wstring> kana2roma(multimap<wstring,wstring>, wstring);
void convertMultiByteToWideChar(const char* , std::wstring& );
const multimap<wstring,wstring>& init(const char*);
const vector<pair<wstring,wstring> >& initvec(const char*);
void initset(const char*, KanaSet&); 
bool ComparePrefix(wstring,wstring);
const vector<wstring> ListMatchPrefix(vector<wstring>& ,wstring);
/*template<typename T>
void OutputVector(const vector<wstring>& v, T& os)
{
	for(vector<wstring>::iterator i = v.begin(); i != v.end();++i) {
		//wcout << *i << endl;
		os << *i << std::endl;
	}
}*/
bool match(vector<wstring>, wstring);
