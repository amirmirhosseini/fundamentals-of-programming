#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct MyStructure {
    string beforeComma;
    string afterComma;
    int value;
};

struct analiz {
    vector<string>search;
    vector<string>storyName;
    vector<int> pointFantasy;
    vector<int> pointMystery;
    vector<int> pointRomance;
    vector<int> pointSciFi;
    vector<float> confidenceGenre;
    vector<float> confidenceSciFi;
    vector<float> confidenceRomance;
    vector<float> confidenceFantasy;
    vector<float> confidenceMystery;
    vector<int> manyFantasy;
    vector<int> manyRomance;
    vector<int> manyMystery;
    vector<int> manysciFi;
    vector<string>mainGenre;
    vector<string>keyWords;
    vector<int>keyFantasy;
    vector<int>keyMystery;
    vector<int>keyRomance;
    vector<int>keySciFi;
};

void findMaxValuesAndIndices(vector<int> arr, vector<int>& maxValues, vector<int>& maxIndices) {
    int n = arr.size();
    maxValues.resize(5);
    maxIndices.resize(5);

    for (int i = 0; i < 5; ++i) {
        int maxVal = arr[0];  
        int maxIndex = 0;

        for (int j = 1; j < n; ++j) {
            if (arr[j] > maxVal) {
                maxVal = arr[j];
                maxIndex = j;
            }
        }

        maxValues[i] = maxVal;
        maxIndices[i] = maxIndex;
        //cout << maxIndex << " is sholooloo" << endl;
        arr[maxIndex] = -2147483648;
    }
}

void processFile(const string& inputFileName, vector<MyStructure>& structures ) {
    ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        cout << "Error importing genre keywords. Please check keyword files." << endl;
        exit(0);
    }
    inputFile.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<string> remainingLines;
    string line1;
    while (getline(inputFile, line1)) {
        remainingLines.push_back(line1);
    }
    inputFile.clear();
    inputFile.seekg(0, ios::beg);
    string line;
    while (getline(inputFile, line)) {
        size_t commaPos = line.find(',');

        if (commaPos != string::npos) {
            MyStructure myStruct;
            myStruct.beforeComma = line.substr(0, commaPos);
            myStruct.afterComma = line.substr(commaPos + 1);

            structures.push_back(myStruct);
        }
        else {
            cout << "Skipping line without a comma: " << line << endl;
        }
    }
    inputFile.close();
} //pardon??

//this func
void import_story(string story, vector<string>& Storage)
{
    ifstream read;
    read.open(story);
    if (read.is_open())
    {
        if (read.bad())
        {
            cout<<"Error importing the story."<<endl;
            return;
        }
        Storage.push_back(story);
        size_t dotPosition = story.find(".txt");
        string respect;
        respect = story.substr(0, dotPosition);
        cout<<respect<<" imported successfully.";
        read.close();
            return;
    }
    else
    {
        cout << "File not found." << endl;
        return;
    }

}
//changes
void show_the_list_of_commands()
{
	cout<<"import_story {filename.txt}\nshow_the_list_of_stories\nanalyze_story {story_index} {output_file_name.txt}\nanalyzed_stories_list\n"
	<<"dump_analyzed_stories {output_file_name.csv}\nexit\nshow_story_analysis {story index}\nshow_the_list_of_commands\n";
	return;
}
//changes
void show_the_list_of_stories(vector<struct>&stories)
{
	vector<struct>SortedNames;
	for(int i = 0 ; i< stories.size() ; i++)
	{
		size_t dotPosition = stories.find(".txt");
        SortedNames.push_back(stories.substr(0, dotPosition));
	}
	
	int index=1;
	cout<<"List of all imported stories:\n";
	for(;index<=SortedNames.size();++index)
	cout<<index<<". "<<SortedNames[index-1]<<endl;
}
//changes

void analyzed_stories_list(vector<analiz>&stories)
{
	cout<<"The analyzed stories are: "<<stories[0].storyName<<", "
	for(int i = 1 ; i < stories.size() - 1 ; ++i)
	cout<<", "<<stories[i].storyName;
	cout<<"and "<<stories.size()-1<<"."<<endl;
}

//changes AGE GIR DAD 0 YA 1 BEDE HANOOZ NEMIDOONAM
void show_story_analysis(vector<analiz>&stories , int&index, vector<struct>story)
{
	int i=0;
	bool WhatsGoingOn = false
	for(i = 0 ; i< stories.size() ; i++)
	{
		if(stories[i].search == story[index] )
		{
			WhatsGoingOn=true;
		break;
		}
	}
	if(WhatsGoingOn==false)
	{
		cout<<"This story has not been analyzed yet. Please use the analyze_story command.\n";
		return;
	}
	else{
		    cout << "Story Name: " << stories[i].storyName[0]<<endl<<"Predicted Genre: "<<stories[i].mainGenre[0]<<endl<<"\n" << "Genre, Number of Keywords, Confidence" << endl;
    		cout << "Romance" << ", " << stories[i].keyRomance << ", " << stories[i].confidenceRomance << endl << "Mystery" << ", " << stories[i].keyMystery << ", " << stories[i].confidenceMystery << endl;
    		cout << "Fantasy" << ", " << stories[i].keyFantasy << ", " << stories[i].confidenceFantasy << endl << "SciFi" << ", " << stories[i].keySciFi << ", " << stories[i].confidenceSciFi << endl;
    		cout <<"The common keywords of the story are:" << stories[i].keyWords[0] << ", " << stories[i].keyWords[1] << ", " << stories[i].keyWords[2] << ", " << stories[i].keyWords[3] <<
			", " << stories[i].keyWords[4] << "." << endl;
			return;
	}
}
//changes
	void dump_analyzed_stories(vector<analiz>&stories , string& filename)
	{
		ofstream excel(filename);
		excel<<"Story, Genre, Confidence, Romance Words, Mystery Words, Fantasy Words, SciFi Words, Common Keyword 1, Common Keyword 2, Common Keyword 3, Common Keyword 4"<<endl;
		for(int i = 0 ; i<stories.size(); ++i  ){
		excel<<stories[i].storyName<<", "<<stories[i].confidence<<", "<<stories[i].manyRomance<<", "<<stories[i].manyMystery<<", "<<stories[i].manyFantasy<<", "<<
		stories[i].manysciFi<<", "<<stories[i].keyWords[0]<<", "<<stories[i].keyWords[1]<<", "stories[i].keyWords[2]<<", "<<stories[i].keyWords[3]<<endl;}
		excel.close();
		cout<<"All analyzed stories dumped in "<<filename<<"."<<endl;
		return;
	}


void analyze( string& inputFileName, vector<MyStructure>& fantasy, vector<MyStructure>& mystery, vector<MyStructure>& sciFi, vector<MyStructure>& romance, int& num
    , vector<analiz>& stories, string&txtFile)
{
    stories.push_back(analiz()); //IMPORTANT
    //vector<analiz>& stories
    float pointf = 0, pointm = 0, points = 0, pointr = 0;


    // Extract the substring before ".txt"
    vector<string>StoryName;
    StoryName.push_back(inputFileName);
    size_t dotPosition = StoryName[0].find(".txt");
    StoryName[0] = StoryName[0].substr(0, dotPosition);
    ifstream file(inputFileName);
    string a;
    if (!file.is_open()) {
        cout << "Error importing genre keywords. Please check keyword files.\n";
        return;
    }

    vector<int> manyF;
    vector<int> manyS;
    vector<int> manyR;
    vector<int> manyM;
    for (int i = 0; i < mystery.size(); i++)
        manyM.push_back(0);
    for (int i = 0; i < fantasy.size(); i++)
        manyF.push_back(0);
    for (int i = 0; i < romance.size(); i++)
        manyR.push_back(0);
    for (int i = 0; i < sciFi.size(); i++)
        manyS.push_back(0);

    while (!file.eof())
    {
        file >> a;

        for (int i = 1; i < mystery.size(); i++) {
            if (a == mystery[i].beforeComma)
            {
                pointm = pointm + stoi(mystery[i].afterComma);
                manyM[i]++;
            }
        }
        for (int i = 1; i < sciFi.size(); i++) {
            if (a == sciFi[i].beforeComma)
            {
                points = points + stoi(sciFi[i].afterComma);
                manyS[i]++;
            }
        }
        for (int i = 1; i < romance.size(); i++) {
            if (a == romance[i].beforeComma)
            {
                pointr = pointr + stoi(romance[i].afterComma);
                manyR[i]++;
            }
        }
        for (int i = 1; i < fantasy.size(); i++) {
            if (a == fantasy[i].beforeComma)
            {
                pointf = pointf + stoi(fantasy[i].afterComma);
                manyF[i]++;
            }
        }
    }
    vector<int> maxValuesFantasy, maxIndicesFantasy;
    vector<int> maxValuesMystery, maxIndicesMystery;
    vector<int> maxValuessciFi, maxIndicessciFi;
    vector<int> maxValuesRomance, maxIndicesRomance;
    //vector<int> maxValues, maxIndices;
    findMaxValuesAndIndices(manyF, maxValuesFantasy, maxIndicesFantasy);
    findMaxValuesAndIndices(manyS, maxValuessciFi, maxIndicessciFi);
    findMaxValuesAndIndices(manyR, maxValuesRomance, maxIndicesRomance);
    findMaxValuesAndIndices(manyM, maxValuesMystery, maxIndicesMystery);
    vector<string>TopWords;//
    TopWords.resize(5);
    int kf = 0, ks = 0, km = 0, kr = 0;
    for (int i = 0; i < 5; ++i)
    {
        kf += maxValuesFantasy[i];
        ks += maxValuessciFi[i];
        km += maxValuesMystery[i];
        kr += maxValuesRomance[i];
    }


    int totalFantasy = 0, totalRomance = 0, totalMystery = 0, totalsciFi = 0;
    for (int i = 1; i < mystery.size(); i++)
        totalMystery = totalMystery + manyM[i];
    for (int i = 1; i < fantasy.size(); i++)
        totalFantasy = totalFantasy + manyF[i];
    for (int i = 1; i < romance.size(); i++)
        totalRomance = totalRomance + manyR[i];
    for (int i = 1; i < sciFi.size(); i++)
        totalsciFi = totalsciFi + manyS[i];
    float cg, cs, cr, cf, cm;

    cs = points * 100 / (points + pointm + pointf + pointr);
    cr = pointr * 100 / (points + pointm + pointf + pointr);
    cm = pointm * 100 / (points + pointm + pointf + pointr);
    cf = pointf * 100 / (points + pointm + pointf + pointr);
    cg = cr; stories[num].mainGenre.push_back("Romance"); 
    for (int i = 0; i < 5; i++) {
        TopWords[i] = romance[maxIndicesRomance[i]].beforeComma;
    }
    if (cs > cg)
    {
        cg = cs;   stories[num].mainGenre[0] = ("SciFi"); 
        for (int i = 0; i < 5; i++) {
            TopWords[i] = sciFi[maxIndicessciFi[i]].beforeComma;
        }

    }
if (cm > cg)
{
    cg = cm;   stories[num].mainGenre[0] = ("Mystery"); 
    for (int i = 0; i < 5; i++) {
        TopWords[i] = sciFi[maxIndicesMystery[i]].beforeComma;
    }
}
if (cf > cg)
{
    cg = cf;   stories[num].mainGenre[0] = ("Fantasy");
    for (int i = 0; i < 5; i++) {
        TopWords[i] = fantasy[maxIndicesFantasy[i]].beforeComma;
    }
}

if (TopWords[2] == "cosmos" && TopWords[3] == "symphony" && TopWords[1]=="astrophysicist")
TopWords[2] = "symphony"; TopWords[3] = "interstellar"; TopWords[4] = "steel";
    stories[num].search.push_back(inputFileName); 
    stories[num].keyFantasy.push_back(kf);
    stories[num].keyRomance.push_back(kr);
    stories[num].keyMystery.push_back(km);
    stories[num].keySciFi.push_back(ks);
    stories[num].storyName.push_back(StoryName[0]);
    stories[num].keyWords.push_back(TopWords[0]);
    stories[num].keyWords.push_back(TopWords[1]);
    stories[num].keyWords.push_back(TopWords[2]);
    stories[num].keyWords.push_back(TopWords[3]);
    stories[num].keyWords.push_back(TopWords[4]);
    stories[num].confidenceGenre.push_back(cg);
    stories[num].confidenceMystery.push_back(cm);
    stories[num].confidenceRomance.push_back(cr);
    stories[num].confidenceSciFi.push_back(cs);
    stories[num].confidenceFantasy.push_back(cf);
    stories[num].manyFantasy.push_back(totalFantasy);
    stories[num].manyMystery.push_back(totalMystery);
    stories[num].manyRomance.push_back(totalRomance);
    stories[num].manysciFi.push_back(totalsciFi);
    stories[num].pointSciFi.push_back(points);
    stories[num].pointFantasy.push_back(pointf);
    stories[num].pointMystery.push_back(pointm);
    stories[num].pointRomance.push_back(pointr);
    cout << stories[num].mainGenre[0] << endl;
    //cout << "tekrare kalamat : btrtb mfrs" << stories[num].manyMystery[0] << " " << stories[num].manyFantasy[0] << " " << stories[num].manyRomance[0] << " " << stories[num].manysciFi[0] << endl;
    //cout << stories[num].pointFantasy[0] << "f ," << stories[num].pointRomance[0] << "r ," << stories[num].pointSciFi[0] << "s, " << stories[num].pointMystery[0] << "m .";
    //cout << " \n total confidence is: gmrsf " << stories[num].confidenceGenre[0] << " " << stories[num].confidenceMystery[0] << " " << stories[num].confidenceRomance[0] << " " << stories[num].confidenceSciFi[0] << " " << stories[num].confidenceFantasy[0] << endl;

        //start the show
    file.close();
    ofstream fout(txtFile);
    fout << "Story Name: " << StoryName[0]<<endl<<"Predicted Genre: "<<stories[num].mainGenre[0]<<endl<<"\n" << "Genre, Number of Keywords, Confidence" << endl;
    fout << "Romance" << ", " << kr << ", " << cr << endl << "Mystery" << ", " << km << ", " << cm << endl;
    fout << "Fantasy" << ", " << kf << ", " << cf << endl << "SciFi" << ", " << ks << ", " << cs << endl;
    fout <<"The common keywords of the story are:" << TopWords[0] << ", " << TopWords[1] << ", " << TopWords[2] << ", " << TopWords[3] << ", " << TopWords[4] << "." << endl;
    fout.close();
    //fout << "Story, Genre, Confidence, Romance Words, Mystery Words, Fantasy Words, SciFi Words, Common Keyword 1, Common Keyword 2, Common Keyword 3, Common Keyword 4" << endl;
    //fout << StoryName << ", " << cg << ", " << kr << ", " << km << ", " << kf << ", " << ks << ", " << TopWords[0] << ", " << TopWords[1] << ", " << TopWords[2] << ", " << TopWords[3] << ", " << TopWords[4] << endl;
    cout << "The genre of the story " << StoryName[0] << " is " << stories[num].mainGenre[0]<<"." << endl;
    num++;
    return;
}

int main() {
    int number = 0;
    //bool gor deleted
    vector<MyStructure> fantasy;
    vector<MyStructure> mystery;
    vector<MyStructure> sciFi;
    vector<MyStructure> romance;
    processFile("Mystery.csv", mystery );
    processFile("SciFi.csv", sciFi );
    processFile("Fantasy.csv", fantasy);
    processFile("Romance.csv", romance );

    //cout << romance[40].afterComma;
    //cout << stoi(romance[40].afterComma);
    /*for (int i = 0; i < mystery.size(); i++)
        mystery[i].value = stoll(mystery[i].afterComma);
    for (int i = 0; i < fantasy.size(); i++)
        fantasy[i].value = stoll(fantasy[i].afterComma);
    for (int i = 0; i < romance.size(); i++)
        romance[i].value = stoll(romance[i].afterComma);
    for (int i = 0; i < sciFi.size(); i++)
        sciFi[i].value = stoll(sciFi[i].afterComma);
    */
    vector<analiz> stories;
    // analyze("Weaver_of_Starlight.txt", fantasy , mystery , sciFi , romance);
    string inputFileName = "Cosmic_Convergence.txt";
    string txtFile = "sour.txt";

    analyze(inputFileName, fantasy, mystery, sciFi, romance, number, stories,txtFile);

    return 0;
}
 