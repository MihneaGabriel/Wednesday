#include"WednesdayRO.cpp"
#include"WednesdayEN.cpp"

int main()
{
    string c;

    cout<<"Select a language(RO/EN): ";
    cin>>c;
    system("cls");

    if( c == "RO" )
        mainRO();
    else if( c == "EN" )
        mainEN();

    return 0;
}
