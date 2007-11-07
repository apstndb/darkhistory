#include <vector>
#include <map>
#include <string>
#include <utility>
#include <boost/shared_ptr.hpp>
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
	public:
	wstring kana;
	wstring yomi;
	wstring& getKana() {return kana;}
	wstring& getYomi() {return yomi;}
	bool operator<(const KanaYomi& r) const {
		return yomi < r.yomi;
	}
};
struct by_kana {};
struct by_yomi {};
struct by_fifo {};
typedef boost::shared_ptr<const KanaYomi> KanaYomiPtr;
class KanaSet {
	typedef multi_index_container<
		KanaYomi,
		indexed_by<
			sequenced<tag<by_fifo> >,
		ordered_unique<tag<by_yomi>,identity<KanaYomi> >,
		ordered_non_unique<
			tag<by_kana>,
		mem_fun<KanaYomi, wstring&, &KanaYomi::getKana> >
			>
			> kanaset_set_t;
	kanaset_set_t kanaset;
	typedef kanaset_set_t::index<by_kana>::type kanaset_kana_index;
	typedef kanaset_set_t::index<by_yomi>::type kanaset_yomi_index;
	typedef kanaset_set_t::index<by_fifo>::type kanaset_fifo_index;
	public:
	KanaYomi searchByYomi(const wstring &yomi);
	//      vector<KanaYomi> searchByKana(const wstring &Kana);

	//	void push(KanaYomi entry);
	//	KanaYomi front() const;
	//	void pop();
};

vector<wstring> kana2roma(multimap<wstring,wstring>, wstring);
void convertMultiByteToWideChar(const char* , std::wstring& );
const multimap<wstring,wstring>& init(const char*);
const vector<pair<wstring,wstring> >& initvec(const char*);
const KanaSet& initset(const char*);
bool ComparePrefix(wstring,wstring);
vector<wstring> ListMatchPrefix(vector<wstring>& ,wstring);
void OutputVector(vector<wstring>);
bool match(vector<wstring>, wstring);
