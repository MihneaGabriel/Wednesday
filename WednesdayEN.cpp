//Lascu Mihnea Gabriel 323AC
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
#include<ctime>
#include<algorithm> // for itr
#include<string>
#define N 891 // nr_pers + costuri totale

using namespace std;
class DISHEN;

class EVENTEN
{
private:
    double liquid[N], cost_castle; // How much liquid does a person consume
    double trans[N], room[N], cost_costume; // How much does makeup cost
    int nr_days;
    string costum[N], food[N];
public:

    EVENTEN( ){
        this->cost_castle = 0;
        this->cost_costume = 0;
        this->nr_days = 0;
    }
    ~EVENTEN(){}

    void Transport( int nr_pers );
    void Food( int nr_pers );
    void Costume( );
    void Room( int nr_pers );
    void Liquid( int nr_pers );
    void Castle( );
    void Write( );

    void SetDay( int nr_days ){ //Setter
        this->nr_days = nr_days;
    }

    friend class DISHEN;
    friend double Total( DISHEN cost );
};
// Metode EVENTEN
void EVENTEN::Transport( int nr_pers )
{
    int nr_autocar = 1, maxcapacity = 50, k = 1, j = 0;
    double totalcost = 0;


    for( int i = 0 ; i < nr_pers ; i++ )
    {
        if( k == maxcapacity ) // The bus is full
        {
            k = 1;
            nr_autocar++; // Go to the next bus
        }
        trans[j++] = nr_autocar;
        k++;
    }

    totalcost = nr_autocar * 5680;
    trans[j++] = totalcost;
}
void EVENTEN::Costume( )
{
    ifstream fin;
    ofstream fout;
    int j = 0;
    double totalcost = 0;
    string masc[5] = {"Vampire","Werewolf","Mermaid","Oracle","Human"};
    int costmonster[5] = {230,555,345,157,55};
    srand(time(0));

    try
    {
        fin.open("PersonalCopy.CSV");
        fout.open("CostEveniment.CSV");
        if( fin.fail() || fout.fail() ) // error message
            throw '1';

        string line, aux1, aux2;

        //extract the second row;
        while( getline(fin, line) )
        {
            stringstream my_stream(line);
            while( getline( my_stream, aux1, ',' ))
            {
                while( getline( my_stream, aux2, ','))
                {
                    my_stream>>aux1;

                    if( aux2 == "Series Cast" || aux2 == "Series Figure")
                    {
                        int n = sizeof(costmonster)/sizeof(costmonster[0]);
                        auto itr = find( costmonster, costmonster + n, costmonster[rand() % 5 ] ); // find the index of a random element in hexa
                        int index = distance(costmonster, itr);

                        costum[j] = masc[index];
                        totalcost = totalcost + costmonster[index];
                        j++;
                    }
                    else
                        costum[j++] = "None";
                }
            }
        }

        totalcost = nr_days * totalcost; // csot per day
        costum[j++] = to_string(totalcost);
        cost_costume = totalcost; // for calculation
        fout.close();
        fin.close();
    }
    catch( char exp )
    {
        if( exp == '1' )
            cout<<"File failed to open!"<<endl;
    }
    catch( int exp )
    {
        cout<<"BUG!"<<endl;
    }

}
void EVENTEN::Food( int nr_pers )
{
    string types[3] = {"Apt to eat anything","Vegetarian","Flexitarian"};
    srand(time(0));

    for( int i = 0 ; i < nr_pers ; i++ )
        food[i] = types[rand() % 3 ];
}
void EVENTEN::Room( int nr_pers )
{
    ifstream fin;
    ofstream fout;
    int c1 = 0, c2 = 0, nr = 1, j = 0; // contor room with 2 pers and with 3 pers
    double totalcost = 0;
    srand(time(0));

    try
    {
        fin.open("PersonalCopy.CSV");
        fout.open("CostEveniment.CSV");
        if( fin.fail() || fout.fail() ) // error message
            throw '1';

        string line, aux1, aux2;

        //extract the second row;

        while( getline(fin, line) )
        {
            stringstream my_stream(line);
            while( getline( my_stream, aux1, ',' ))
            {
                while( getline( my_stream, aux2, ','))
                {
                    my_stream>>aux1;
                    if( aux2 == "Series Figure")
                        {
                            if( j == nr_pers - 132 ) // use for transition between cast and extras
                                nr++;

                            if( c1 == 3 ) // max capacity
                                {
                                    c1 = 0;
                                    totalcost = totalcost + 450;
                                    nr++;
                                }
                            room[j++] = nr; // room number
                            c1++;
                        }
                    else
                    {
                        if( c2 == 2 ) // max capacity
                        {
                            c2 = 0;
                            totalcost = totalcost + 350;
                            nr++;
                        }
                        room[j++] = nr; // room number
                        c2++;

                    }
                }
            }
        }
        fout.close();
        fin.close();

        room[j++] = nr_days * totalcost;
    }
    catch( char exp )
    {
        if( exp == '1' )
            cout<<"File failed to open!"<<endl;
    }


}
void EVENTEN::Liquid( int nr_pers )
{
    double water = 0, coffee = 0, soda = 0; // water coffee soda

    for( int i = 0 ; i < nr_pers ; i++ )
    { // per 3 days
        water += nr_days * 1;
        coffee += nr_days * 0.5;
        soda += nr_days * 0.8;
        liquid[i] = nr_days * ( 1 + 0.5 + 0.8 );
    } // 1l water 0.5l coffee 0.8 soda

    water = ( water / 2 ) * 6 ; // 2l water = 6lei
    coffee = ( coffee / 1 ) * 30; // 1l coffee = 30lei
    soda = ( soda / 2 ) * 8; // 2l soda = 8lei

    liquid[nr_pers] = water + coffee + soda;
}
void EVENTEN::Castle( )
{
    int i = nr_days;
    cost_castle = nr_days * 10000 ;

    while( i )
    {
        if( i % 10 == 0 )
        {
            cost_castle = cost_castle - ( 2/100 * cost_castle );
        }
        i--;
    }
}
void EVENTEN::Write( )
{
        ofstream fout;

        try
        {
            fout.open("CostEveniment.CSV");
            if( fout.fail() )
                throw '1';

            for(int i = 0 ; i < N ; i++ )
                if( i == N-1 )
            {
                fout<<(int)trans[i]<<","
                    <<stoi(costum[i])<<","
                    <<stoi(food[i])<<","
                    <<(int)room[i]<<","
                    <<(int)liquid[i]<<","
                    <<(int)cost_castle<<"\n";
            }
            else
            {
                fout<<trans[i]<<","
                    <<costum[i]<<","
                    <<food[i]<<","
                    <<room[i]<<","
                    <<liquid[i]<<","
                    <<" "<<"\n";
            }
        }
        catch( char exp )
        {
            if( exp == '1' )
                cout<<"File failed to open!"<<endl;
        }

    }

class DISHEN: public EVENTEN
{
protected:
    string Checker( string aux, string key ); // Template specialization
    int nr_pers;
    double cost_food = 0;
    EVENTEN obj;
public:

    DISHEN( EVENTEN obj , int nr_pers );   // Generate types of food
    ~DISHEN( )
    {
        cout<<"The Menu has done succesfully!"<<endl;
    }

    void Write( )
    {
        obj.food[nr_pers] = to_string(cost_food);
        obj.Write();
    }

    friend double Total( DISHEN cost );
};
//Constructori DISHEN
DISHEN::DISHEN( EVENTEN obj , int nr_pers )
{
    // Consideram ca supa nu contine carne
    ofstream fout;
    string supa[7] = {"Vegetables soup", "Chicken broth", "Beef broth", "Mushrooms soup", "Lentil soup", "Tripe broth", "Fish broth" };
    string fprincip[6] = {"Vegetables pasta", "Curry chicken", "Tuna pasta", "Gratin Vegetables", "Vegan Noodles", " Tuna salad" };
    string desert[5] = {"Tiramisu", "Cheesecake", "Pavlova", "Banana bread", "Lava cake" };
    double totalcost[3] = {}; // food price
    srand(time(0));

    this->nr_pers = nr_pers;
    this->obj = obj;

    try
    {
        fout.open("MeniuMancare.CSV");
        if( fout.fail() ) // error message
            throw '1';

        for( int i = 0 ; i < nr_pers ; i++ )
        {
          for( int j = 0 ; j < obj.nr_days / 3 + 1; j++ )
        {
            if( obj.food[i] == "Apt to eat anything")
            {
                fout<<supa[rand()%7]<<","
                    <<fprincip[rand()%6]<<","
                    <<desert[rand()%5]<<",,";

                totalcost[0] = totalcost[0] + 40;
            }
            else if( obj.food[i] == "Vegetarian" )
            {
                string aux = "";
                while( aux == "" ) // always find a var
                    aux = Checker( supa[rand()%7], "soup" );
                fout<<aux<<",";

                aux = "";
                while( aux == "" )
                    aux = Checker( fprincip[rand()%6], "Vegetables");
                fout<<aux<<","
                    <<desert[rand()%5]<<",,"; // All vegetarians dont have restriction to serve desert

                totalcost[1] = totalcost[1] + 33;
            }
            else if( obj.food[i] == "Flexitarian")
            {
                string aux = "";
                while( aux == "" ) // always find a var
                    aux = Checker( supa[rand()%7], "Fish" );
                fout<<aux<<",";

                aux = "";
                while( aux == "" )
                    aux = Checker( fprincip[rand()%6], "Tuna");
                fout<<aux<<","
                    <<desert[rand()%5]<<",,";

                totalcost[2] = totalcost[2] + 46;
            }
            else throw 1; // error message

            }
            fout<<"\n";
        }

        for( int i = 0 ; i < 3 ; i++ )
            cost_food = cost_food + (obj.nr_days * totalcost[i]); // total cost of food per 3 days

        fout.close();
    }
    catch( char exp )
    {
        if( exp == '1' )
            cout<<"File failed to open!"<<endl;
    }
    catch( int exp )
    {
        if( exp == 1 )
            cout<<"Someone is not serving lunch!"<<endl;
    }

}
// Metode DISHEN
string DISHEN::Checker( string aux, string key )
{
    size_t found = aux.find(key);
    if( found !=  string::npos )
        return aux;

    return "";
}

double Total( DISHEN cost )
{
    double totalcost = 0;
    int itr = cost.nr_pers;

    totalcost = 2 * cost.obj.trans[itr] + cost.obj.cost_costume + cost.cost_food + cost.obj.room[itr] + cost.obj.liquid[itr] + cost.obj.cost_castle; // cost transport dus-intors
    totalcost = totalcost / 4.62 ;// covert lei to dollars

    return totalcost;
}
template<class T>
T FigureEN() // Generate random names (RANDOM)
{
    ofstream fout; // copy file;
    ifstream fin; // original file
    string line;
    int line_number = 0;
    srand(time(0));

    string second[163]= {"Antarctican","Flying","Electric","Fractured","Broken","Clear","Muddy","Yellow","Naked","Invisible","Hollow","Crass","Light","Dark","Chocolate","Riff","Mind","Heartless","Rock","Gods of","Sacrifice to","Master","Sleazy","Sisters of","Brothers of","Angry","Dying","Bloody","Crazy","Shocking","Quiet","Sick","Cynical","Complete","Rude","Spicy","Hurt","Aquatic","Demonic","Obselete","Grieving","Deep","Ancient","Dead","Impossible","Violent","Juvenile","Real","Long","Meek","Orange","Grey","Moaning","Jobless","Awful","Typical","Acid","Little","Obscene","Dry","Sticky","Rapid","Addictive","Cool","Tame","Royal","Cruel","Loud","High","Big","Chemical","Mighty","Wretched","Drunk","General","Daily","Fluffy","Elfin","Two","Three","Scandalous","Four","Five","Only","Sex","Rustic","Empty","Ugly","Evil","Disturbed","Unnatural","Ghostly","Heavy","Modern","Fresh","Ragged","Innocent","Acoustic","Rich","Lewd","Perverted","Infernal","Abusive","Quick","Blue-eyed","Stormy","Icy","True","Chilly","Jaded","Black","Creepy","Screaming","Stabbing","Tilted","Spurned","Unreal","Pissed","Awesome","Spinal","Dirty","Black","Scarlet","Gang of","Major","Headless","Tortured","Hybrid","Sonic","Riot","Hell","Damned","Pink","White","Green","Insidious","Spiritual","Broken","Abusive","Dark","Real","Enchanted","Imaginary","Daily","Lame","Future","Automatic","Shrill","Scarce","Noctural","Asian","Streetlight"};
    string third[137] = {"Gods","Devil","Letter","Men","Ladies","Widow","Statement","Scarecrow","Chickens","Animal","Mice","Cheese","Punishment","Thrill","Pain","Death","Truth","Temper","Summer","Anarchy","Antichrist","Self","Face","Tears","Story","Blows","Invention","Inc.","Window","Thrones","Surgery","Metal","Meeks","Ancestors","Stoners","Spiders","Brothers","Sisters","Of Fate","Tramps","Behaviour","Road","Tree","Beetles","Sunday","Zone","Boys","Girls","Flag","Dragon","Kiss","Youth","Space","Island","Cream","Punk","Tones","Enemy","Fighters","Birds","Pistols","Mind","Bait","Worms","Fly","Persuasion","Roof","Discovery","Children","School","Theory","Coders","Zebras","Noobs","Crowd","Tail","Nest","Library","Ship","Magic","Question","Error","Rhythm","Babies","Cobwebs","Turn","Aliens","Division","Things","Attraction","Ministers","Ritual","Guns","Night","Winter","Company","Picture","Impulse","Force","Moments","Caress","Skyline","Friday","Abuse","Afternoon","Morning","Evening","Nobodies","Remains","Waters","Party","Martians","Fire","Harvest","Star","911","Route","War","Sky","Roses","Threat","Desert","Head","Brigade","Victim","Generator","Zombies","Church","Dream","Nightmare","Heads","Jam","Horsemen","Symptoms","Emissions","Vengeance","Frustration"};
    try
    {
        fin.open("Personal.CSV");
        fout.open("PersonalCopy.CSV");

        if( fout.fail() || fin.fail() ) // error message
            throw '1';

        while( getline(fin,line) )
        {
            line_number++;
            fout<<line<<"\n"; // File copy

        }

        fout.close();
        fin.close();

        fin.open("PersonalCopy.CSV");
        fout.open("PersonalCopy.CSV", ios::app );
        if( fout.fail() || fin.fail() ) // error message
            throw '1';

        for( int i = 0 ; i < 132 ; i++ )
            if( fin.is_open() )
            {
                line_number++;
                fout<<second[rand() % 163] << " " << third[rand() % 137]<<","<<"Series Figure"<<"\n";
            }
    }
    catch( char exp )
    {
        if( exp == '1' )
            cout<<"File failed to open!"<<endl;
    }

    return line_number;
}

int mainEN()
{
    EVENTEN ev;
    int nr_pers, nr_days;

    nr_pers = FigureEN<int>();
    cout<<"Write a day number: ";
    cin>>nr_days;

    ev.SetDay( nr_days );

    ev.Transport( nr_pers ); // calculate trasnport
    ev.Costume( ); // calculate cost of costumes
    ev.Food( nr_pers ); // calculate types of food
    ev.Room( nr_pers ); // assign the rooms
    ev.Liquid( nr_pers ); // calculate liquid;
    ev.Castle( ); // rent for castle

    DISHEN d( ev, nr_pers );

    d.Write( );

    cout<<"Movie costs: "<<(int)Total(d)<<" $"<<endl<<endl;

    return 0;
}
