#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

// Student number: Tomas Vosylius / s1042957

using namespace std;

struct Length
{
	int minutes;							// #minutes (0..)
	int seconds;							// #seconds (0..59)
};

struct Track
{
	string artist;                          // name of artist
	string cd;                              // cd title
	int    year;                            // year of appearance (if known)
	int    track;							// track number
	string title;                           // track title
	string tags;                            // tags
	Length time;							// playing time
	string country;                         // main countr(y/ies) of artist
};

struct TrackDisplay
{
	bool showArtist;						// if true, show name of artist
	bool showAlbum;							// if true, show cd title
	bool showYear;							// if true, show year of appearance
	bool showTrack;							// if true, show track number
	bool showTitle;							// if true, show track title
	bool showTags;                          // if true, show tags
	bool showLength;						// if true, show playing time
	bool showCountry;                       // if true, show countr(y/ies) of artist
};

/* For testing purposes, you can use the below defined, very small, music database.
   This is also convenient if you have not yet implemented reading the database file.
*/
vector<Track> testDB = {{"Adele",                          "19",                          2008,1, "Daydreamer",                  "pop,debut album",                   { 3,40},"England"}
                       ,{"Adele",                          "19",                          2008,10,"My same",                     "pop,debut album",                   { 3,15},"England"}
                       ,{"Adele",                          "19",                          2008,11,"Tired",                       "pop,debut album",                   { 4,18},"England"}
                       ,{"Adele",                          "19",                          2008,12,"Hometown glory",              "pop,debut album",                   { 4,31},"England"}
                       ,{"Adele",                          "19",                          2008,2, "Best for last",               "pop,debut album",                   { 4,18},"England"}
                       ,{"Adele",                          "19",                          2008,3, "Chasing pavements",           "pop,debut album",                   { 3,30},"England"}
                       ,{"Adele",                          "19",                          2008,4, "Cold shoulder",               "pop,debut album",                   { 3,11},"England"}
                       ,{"Adele",                          "19",                          2008,5, "Crazy for you",               "pop,debut album",                   { 3,28},"England"}
                       ,{"Adele",                          "19",                          2008,6, "Melt my heart to stone",      "pop,debut album",                   { 3,23},"England"}
                       ,{"Adele",                          "19",                          2008,7, "First love",                  "pop,debut album",                   { 3,10},"England"}
                       ,{"Adele",                          "19",                          2008,8, "Right as rain",               "pop,debut album",                   { 3,17},"England"}
                       ,{"Adele",                          "19",                          2008,9, "Make you feel my love",       "pop,debut album",                   { 3,32},"England"}
                       ,{"Adele",                          "21",                          2011,1, "Rolling in the deep",         "pop",                               { 3,49},"England"}
                       ,{"Adele",                          "21",                          2011,10,"Lovesong",                    "pop",                               { 5,16},"England"}
                       ,{"Adele",                          "21",                          2011,11,"Someone like you",            "pop",                               { 4,47},"England"}
                       ,{"Adele",                          "21",                          2011,2, "Rumour has it",               "pop",                               { 3,43},"England"}
                       ,{"Adele",                          "21",                          2011,3, "Turning tables",              "pop",                               { 4,10},"England"}
                       ,{"Adele",                          "21",                          2011,4, "Don't you remember",          "pop",                               { 4, 3},"England"}
                       ,{"Adele",                          "21",                          2011,5, "Set fire to the rain",        "pop",                               { 4, 1},"England"}
                       ,{"Adele",                          "21",                          2011,6, "He won't go",                 "pop",                               { 4,37},"England"}
                       ,{"Adele",                          "21",                          2011,7, "Take it all",                 "pop",                               { 3,48},"England"}
                       ,{"Adele",                          "21",                          2011,8, "I'll be waiting",             "pop",                               { 4, 1},"England"}
                       ,{"Adele",                          "21",                          2011,9, "One and only",                "pop",                               { 5,48},"England"}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,1, "Call me star",                "alternative,rock",                  { 3,54},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,2, "El centro",                   "alternative,rock,instrumental",     { 8,25},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,3, "Dirt preachers",              "alternative,rock",                  { 3,44},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,4, "This is where it falls apart","alternative,rock",                  { 7, 2},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,5, "Mellowing",                   "alternative,instrumental",          { 3,11},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,6, "Open passageways",            "alternative,rock",                  { 3,14},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,7, "Instrumental 2 (welcome to the caveman future)"
                                                                                                                                ,"alternative,rock,instrumental",     { 2,33},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,8, "Talisman",                    "alternative,rock",                  { 6, 7},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,9, "Blood and sand / milk and endless waters","alternative,rock",      { 7,20},"U.S.A."}
                       ,{"The decemberists",               "The tain",                    2005,1, "The tain (parts i-iv)",       "progressive,experimental,folk,rock",{18,35},"U.S.A."}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,1, "The sun roars into view",     "jazz,instrumental,experimental",    { 7,37},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was"  ,2015,2, "Won't be a thing to become",  "jazz,instrumental,experimental",    { 3,24},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,3, "In the vespers",              "jazz,instrumental,experimental",    { 6, 2},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,4, "And still they move",         "jazz,instrumental,experimental",    { 2,56},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,5, "With the dark hug of time",   "jazz,instrumental,experimental",    { 6,34},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,6, "The rest of us",              "jazz,instrumental,experimental",    { 6,30},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,7, "Never were the way she was",  "jazz,instrumental,experimental",    { 8,12},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,8, "Flight",                      "jazz,instrumental,experimental",    { 1,38},"U.S.A.,Canada"}
};

const unsigned int MAX_LINES_PER_TRACK = 8;

bool match(string sub, string source)
{
    //  Precondition:
    assert(true);
    /*  Postcondition:
        Result is true only if sub is a literal (case sensitive) sub string of source.
    */
    return source.find(sub) != string::npos;
}


ostream& operator<<(ostream& out, const Length length)
{
    // Precondition:
    assert(true);
    /*  Postcondition:
        the value of length is shown via out in the format: minutes, ':', seconds (two digits)
    */
    out << length.minutes << ":" << length.seconds;
    if(length.minutes >= 0 && length.seconds >= 0 && length.seconds <= 59)
    {
        return out;
    }
    else
    {
        cout << "Error encountered when reading length. Check if length is specified correctly." << endl;
    }
}

istream& operator>>(istream& in, Length& length)
{
    // Precondition:
    assert(true);
    /*  Postcondition:
        the value of length has been read from in: first minutes, then ':', then seconds
    */
    char ignore;
    in >> length.minutes >> ignore >> length.seconds;
    return in;
}

Length operator+(const Length& a, const Length& b)
{
    //  Precondition:
    assert(0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60);
    /*  Postcondition:
        Result is the sum of a and b.
    */
    Length sum;
    sum.seconds = a.seconds + b.seconds;
    sum.minutes = a.minutes + b.minutes;
    while(sum.seconds >= 60)
    {
        sum.minutes += 1;
        sum.seconds -= 60;
    }
    return sum;
}


istream& operator>>(istream& in, Track& track)
{
    //  Precondition:
    assert(true);
    /*  Postcondition:
        the content of the first 8 lines from in have been read and are stored in the corresponding members of track.
        The following (empty) line from in has also been read.
    */

    // This is not a good solution, but I didn't fully understand
    // if we supposed to use both [overload >> in,Lenght] and getline
    // so i mixed them and this is what I've got

    int line = 0; // simply which line of data we are reading
    string readline; // used for string lines
    while(line < MAX_LINES_PER_TRACK)
    {
        switch(line)
        {
            case 2: in >> track.year;   break; // year
            case 3: in >> track.track;  break; // track
            case 6: in >> track.time;   break; // time
            default:
            {
                getline(in, readline);
                if(in.fail()) return in;
                while(readline.length() == 0)
                {
                    // if the line is empty and we are not at the end of track reading, skip the empty line
                    getline(in, readline);
                    if(line >= MAX_LINES_PER_TRACK)
                    {
                        // this was the very last line
                        return in;
                    }
                }
                // Switching again, not the smartest way
                switch(line)
                {
                    case 0: track.artist = readline; break; // artist
                    case 1: track.cd = readline; break; // cd
                    case 4: track.title = readline; break; // title
                    case 5: track.tags = readline; break; // tags
                    case 7: track.country = readline; break; // country
                }
            }
        }
        line++;
    }
    return in;
}

void show_track(Track track, TrackDisplay lt)
{
    //  Precondition:
    assert(true);
    /*  Postcondition:
        only the members of track are shown for which the corresponding member in lt is true.
    */
    if(lt.showArtist)   cout << "[Artist: " << track.artist << "] ";
    if(lt.showAlbum)    cout << "[Album: "  << track.cd     << "] ";
    if(lt.showYear)     cout << "[Year: "   << to_string(track.year)    << "] ";
    if(lt.showTrack)    cout << "[Track: "  << to_string(track.track)   << "] ";
    if(lt.showTitle)    cout << "[Title: "  << track.title  << "] ";
    if(lt.showTags)     cout << "[Tags: "   << track.tags   << "] ";
    if(lt.showLength)   cout << "[Length: " << track.time   << "] ";
    if(lt.showCountry)  cout << "[Country: "<< track.country<< "] ";
    cout << endl;
}
/** Part 3
*/
int match_tracks(vector<Track>& tracks, string track, bool display)
{
    //  Precondition
    assert(true);
    /*  Postcondition
        returns count of matched tracks with `track`
    */
    int cnt = 0;
    TrackDisplay options;
    options.showArtist  = true;
    options.showAlbum   = true;
    options.showYear    = true;
    options.showTrack   = true;
    options.showTitle   = true;
    options.showLength  = true;
    options.showTags    = true;
    options.showCountry = true;

    for(int t = 0; t < tracks.size(); t++)
    {
        if(match(track, tracks[t].title))
        {
            if(display)
            {
                show_track(tracks[t], options);
            }
            cnt ++ ;
        }
    }
    return cnt;
}
bool find_string_in_vector(vector<string>& vec, string value)
{
    //  Precondition
    assert(true);
    /*  Postcondition
        true if given string value is found in vector vec
    */
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i] == value) return true;
    }
    return false;
}
int match_artists(vector<Track>& tracks, string artist, bool display)
{
    //  Precondition
    assert(true);
    /*  Postcondition
        returns count of matched artists with `artist`
    */
    int cnt = 0;
    // Display options
    TrackDisplay options;
    options.showArtist  = true;
    vector<string> found;

    for(int t = 0; t < tracks.size(); t++)
    {
        if(match(artist, tracks[t].artist) && !find_string_in_vector(found, tracks[t].artist))
        {
            // Haven't found this one yet
            if(display)
            {
                show_track(tracks[t], options);
            }
            // Append it to the vector
            found.push_back(tracks[t].artist);
            cnt ++ ;
        }
    }
    return cnt;
}
int match_cds(vector<Track>& tracks, string artist, bool display)
{
    //  Precondition
    assert(true);
    /*  Postcondition
        returns count of matched albums with `artist`
    */
    int cnt = 0;
    // Display options
    TrackDisplay options;
    options.showArtist  = true;
    options.showAlbum   = true;
    options.showYear    = true;
    vector<string> found;

    for(int t = 0; t < tracks.size(); t++)
    {
        if(match(artist, tracks[t].artist) && !find_string_in_vector(found, tracks[t].cd))
        {
            // Haven't found this one yet
            if(display)
            {
                show_track(tracks[t], options);
            }
            // Append it to the vector
            found.push_back(tracks[t].cd);
            cnt ++ ;
        }
    }
    return cnt;
}
int number_of_cds(vector<Track>& tracks)
{
    //  Precondition:
    assert(true);
    /*  Postcondition:
        returns number of cds in trackdb
    */
    int cnt = 0;
    vector<string> found;

    for(int t = 0; t < tracks.size(); t++)
    {
        if(!find_string_in_vector(found, tracks[t].cd))
        {
            found.push_back(tracks[t].cd);
            cnt++;
        }
    }
    return cnt;
}
/** Part 4
*/
bool read_track(istream& file, Track& currentTrack)
{
    //  Precondition:
    assert(true);
    /*  Postcondition:
        returns true if track was read successfully and it's not end of file
    */
    if(file >> currentTrack) return true;
    return false;
}
int read_tracks(string filename, vector<Track>& tracks)
{
    //  Precondition:
    assert(true);
    /*  Postcondition:
        returns entries of tracks in file 'filename'
    */
    int cnt = 0;

    ifstream file(filename);
    if(file.fail())
    {
        cout << "Failed to open file \"" << filename << "\"" << endl;
        return -1;
    }
    else
    {
        Track currentTrack;
        TrackDisplay options = {true, true, true, true, true, true, true, true};

        while(read_track(file, currentTrack))
        {
            // show_track(currentTrack, options);
            cnt ++ ;
        }
    }
    return cnt;
}


int main()
{
    //  Precondition:
    assert(true);
    /*  Postcondition:
        the music database "Tracks.txt" has been read (if present and correctly formatted).
        The assignment queries have been executed and their result has been shown on screen.
        In case of the bonus assignment, the user has been able to query the database and has
        seen the results of these queries.
    */

    vector<Track> tracksDB;
    int cnt = read_tracks("Tracks.txt", tracksDB);
    cout << "Track entries in \"Tracks.txt\": " << cnt << endl;

    #define RUN_TEST 0
    #if RUN_TEST
        char display;

        string track;
        cout << "enter track to match" << endl;
        cin >> track;
        cout << "display output? y/n" << endl;
        cin >> display;
        cnt = match_tracks(tracksDB, track, (display == 'y'));
        cout << "track matches: " << cnt << endl;

        string artist;
        cout << "enter artist to match" << endl;
        cin >> artist;
        cout << "display output? y/n" << endl;
        cin >> display;
        cnt = match_artists(tracksDB, artist, (display == 'y'));
        cout << "artist matches: " << cnt << endl;

        string cd;
        cout << "enter cd to match" << endl;
        cin >> cd;
        cout << "display output? y/n" << endl;
        cin >> display;
        cnt = match_cds(tracksDB, cd, (display == 'y'));
        cout << "cds matches: " << cnt << endl;

        cnt = number_of_cds(tracksDB);
        cout << "cd count: " << cnt << endl;
    #endif
	return 0;
}

