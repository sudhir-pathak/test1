#include <stdio.h>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;


class Items
{
private:
	map<int, string> items;
public:
	Items () { }
	~Items () { }
	void AddItem(int i, const string& name) { items[i] = name; }
	string GetItemName(int i) { return  items[i]; }
	void Print (const char*);
};

void Items::Print (const char* s)
{
	printf ("%s\n", s);
	for (map<int, string>::iterator it=items.begin(); it != items.end (); it++)
		printf ("<%d> -- <%s>\n", it->first, it->second.c_str());
}

template <typename T>
class ListItems
{
private:
	vector<T> items;
public:
	ListItems () { }
	~ListItems () { /*printf ("DELETED ListItems\n");*/ } 
	void AddItem(T i) { items.push_back(i); }
	void Print (const char* s);

	typedef typename vector<T>::iterator iterator;
	typedef typename vector<T>::const_iterator const_iterator;
	iterator begin() { return items.begin(); }
	iterator end() { return items.end(); }
};

template <typename T>
void ListItems<T>::Print (const char* s)
{
	if (strlen(s) > 0) printf ("%s\n", s);
	for (typename vector<T>::iterator it=items.begin(); it != items.end (); it++) cout << "<" << *it << "> ";
	cout << endl;
}



class ItemsCountMap
{
private:
	map<int, int> icm;

	typedef pair<int, int> P;
	bool static compFunc (P elem1, P elem2) { return elem1.second > elem2.second; }

public:
	ItemsCountMap () { }
	~ItemsCountMap () { }
	void AddItem(int i) { icm[i] += 1; }
	ListItems<int> ReturnItemsByCount ();
	void Print (const char*);
};

void ItemsCountMap::Print (const char* s)
{
	printf ("%s\n", s);
	for (map<int, int>::iterator it=icm.begin(); it != icm.end (); it++)
		printf ("<%d> -- <%d>\n", it->first, it->second);
}

ListItems<int> ItemsCountMap::ReturnItemsByCount ()
{
	ListItems<int>  ibc;

	set<P, bool (*)(P, P) > icmbyc(icm.begin(), icm.end(), compFunc);
	for (set<P, bool (*)(P, P) >::iterator it=icmbyc.begin(); it!=icmbyc.end(); it++) {
		ibc.AddItem (it->first);
	}

	return ibc;
}

class Item2ListMap
{
private:
	map<int, ListItems<int> > i2lm;
public:
	Item2ListMap() {}
	void AddListItem (int i, int l) { i2lm[i].AddItem(l); }
	ListItems<int> GetListItem (int i) { return i2lm[i]; }
	void Print (const char*);
};

void Item2ListMap::Print (const char* s)
{
	for (map<int, ListItems<int> >::iterator it1=i2lm.begin(); it1 != i2lm.end (); it1++) {
		printf ("%s <%d> are:", s, it1->first);
		it1->second.Print ("");
	}
	printf ("\n");
}

class SongsPicker
{
private:
	Item2ListMap* friends;
        Item2ListMap* songsliked;
	SongsPicker () { }
public:
	SongsPicker (Item2ListMap* f, Item2ListMap* s) : friends(f), songsliked(s) { }
	~SongsPicker () { }
	ListItems<string> ReturnTop3Songs (int uid, Items& songs);
};

ListItems<string> SongsPicker::ReturnTop3Songs (int uid, Items& songs)
{
	//1. Find Friend of uid
	ListItems<int> f = friends->GetListItem(uid);

	//2. Find Songs and like count among the ones liked by Friends
	ItemsCountMap icm;
	for (ListItems<int>::iterator it=f.begin(); it!=f.end(); it++) {
		ListItems<int> s = songsliked->GetListItem(*it);
		s.Print ("Songs Liked by this User");

		for (ListItems<int>::iterator it2=s.begin(); it2!=s.end(); it2++) {
			icm.AddItem (*it2);
		}
	}

	icm.Print ("Songs and their liked count for this User");

	//3. Sort Songs in order of liked
	//4. Populate List by top 3
	ListItems<int> sortedsongs = icm.ReturnItemsByCount ();
	sortedsongs.Print ("Songs in sorted order");

	ListItems<string> top3songs;

	int i=0;
	for (ListItems<int>::iterator it=sortedsongs.begin(); it !=sortedsongs.end(); it++,i++) {
		if (i<3) {
			string s = songs.GetItemName(*it);
			top3songs.AddItem (s);
		} else break;
	}

	return top3songs;
}

void BuildUserList (Items& users)
{
	users.AddItem (1, "Ram");
	users.AddItem (2, "Shyam");
	users.AddItem (3, "Krishna");
	users.AddItem (4, "Madhusudan");
	users.AddItem (5, "Gopal");
}

void BuildSongsList (Items& songs)
{
	songs.AddItem (1000, "Songs0");
	songs.AddItem (1001, "Songs1");
	songs.AddItem (1002, "Songs2");
	songs.AddItem (1003, "Songs3");
	songs.AddItem (1004, "Songs4");
	songs.AddItem (1005, "Songs5");
}

void BuildFriendList (Item2ListMap* fm)
{
	fm->AddListItem(1,2);
	fm->AddListItem(1,3);
	fm->AddListItem(1,4);
	fm->AddListItem(1,5);

	fm->AddListItem(2,1);
	fm->AddListItem(2,3);
}

void BuildSongsLikedList (Item2ListMap* sl)
{
	sl->AddListItem(1,1001);
	sl->AddListItem(1,1002);
	sl->AddListItem(1,1005);

	sl->AddListItem(2,1001);
	sl->AddListItem(2,1002);
	sl->AddListItem(2,1005);

	sl->AddListItem(3,1000);
	sl->AddListItem(3,1004);
	sl->AddListItem(3,1005);

	sl->AddListItem(4,1003);
	sl->AddListItem(4,1004);
	sl->AddListItem(4,1005);

	sl->AddListItem(5,1003);
	sl->AddListItem(5,1004);
	sl->AddListItem(5,1005);
}

int main (int argc, char* argv[])
{
	Items users, songs;
	BuildUserList (users);
	BuildSongsList (songs);

	users.Print ("All User List");
	songs.Print ("All Songs List");

	Item2ListMap* friends = new Item2ListMap;
	Item2ListMap* songsliked = new Item2ListMap;
	BuildFriendList (friends);
	BuildSongsLikedList (songsliked);

	friends->Print ("Friends of");
	songsliked->Print ("Songs Liked by");

	SongsPicker sp (friends, songsliked);

	ListItems<string> sl = sp.ReturnTop3Songs(1, songs);
	printf ("Top 3 songs for <%s> ", users.GetItemName(1).c_str ());
	sl.Print ("are:");

	ListItems<string> s2 = sp.ReturnTop3Songs(2, songs);
	printf ("Top 3 songs for <%s> ", users.GetItemName(2).c_str ());
	s2.Print ("are:");

	delete friends;
	delete songsliked;
}
