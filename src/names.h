#define ERROR_MESSAGES 12
struct Namen
{
	char b[6];
};
const char error_m[ERROR_MESSAGES][21]=
{
        "OK",
        "Technology availible",
        "Building availible",
        "enough Minerals",
        "enough Gas",
        "Supply satisfied",
        "Larva availible",
        "Worker availible",
        "researched",
        "Timeout",
        "Too many buildings",
        "Expansion availible"};


const char error_sm[ERROR_MESSAGES]=
{
	        'o','t','b','m','g','s','l','w','r','t','y','E'
};

const Namen kurz[3][60]=
{
	{
	{"SCV  "},{"Marin"},{"Ghost"},{"Vultu"},{"Golia"},{"STank"},{"FiBat"},{"Medic"},{"Wrait"},
	{"SciVe"},{"Drops"},{"BCrui"},{"Valky"},{"CommC"},{"Depot"},{"Barra"},{"Acade"},
	{"Facto"},{"StarP"},{"SciLa"},{"Engin"},{"Armor"},{"MisTu"},{"Bunke"},{"ComSa"},{"NucSi"},
	{"ConTo"},{"CovOp"},{"PhyLa"},{"MasSh"},{"StimP"},{"LockD"},{"EMPSw"},{"SMine"},{"SiegM"},
	{"Irrad"},{"YamaG"},{"Cloak"},{"PersC"},{"Resto"},{"OptcF"},{"U238S"},{"IonTh"},{"TitaR"},
	{"OculI"},{"MoebR"},{"ApolR"},{"ColoR"},{"CaduR"},{"CharB"},{"InfAr"},{"InfWe"},{"VehAr"},
	{"VehWe"},{"ShpAr"},{"ShpWe"},{"NucWa"},{"NULL!"},{"Refin"},{">>Gas"},{">>Min"}
	},


	{
	{"Probe"},{"DarkT"},{"DarkA"},{"Probe"},{"Zealo"},{"HighT"},{"Archo"},{"Reave"},{"Corsa"},
	{"Shutt"},{"Scout"},{"Arbit"},{"Carri"},{"Obser"},{"Nexus"},{"RobFa"},{"Pylon"},
	{"ObsTy"},{"GateW"},{"Photo"},{"Cyber"},{"Citad"},{"TempA"},{"Forge"},{"StarG"},{"Fleet"},
	{"ArbTr"},{"RobBy"},{"Shiel"},{"PsiSt"},{"Hallu"},{"Recal"},{"Stasi"},{"Disru"},{"MindC"},
	{"Maels"},{"Singu"},{"LegEn"},{"ScrbD"},{"ReavC"},{"GraDr"},{"Senso"},{"GraBo"},{"KhaAm"},
	{"ApiaS"},{"GraTh"},{"CarCa"},{"KhaCo"},{"ArgJe"},{"ArgTa"},{"Armor"},{"Plati"},{"Groun"},
	{"AirWe"},{"PShie"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"Assim"},{">>Gas"},{">>Min"}
	},
		
	{
	{"Drone"},{"ZLing"},{"Hydra"},{"Ultra"},{"Defil"},{"Lurkr"},{"Overl"},{"Mutal"},{"Guard"},
	{"Queen"},{"Scour"},{"Devou"},{"Hatch"},{"Lair "},{"Hive "},{"Nydus"},{"HyDen"},{"DeMou"},
	{"GSpir"},{"QNest"},{"EvoCh"},{"UCave"},{"Spire"},{"SPool"},{"Creep"},{"Spore"},{"Sunkn"},
	{"VSacs"},{"Anten"},{"Pneum"},{"Boost"},{"Adren"},{"Muscu"},{"Groov"},{"Gamet"},
	{"MNode"},{"Chiti"},{"Anabo"},{"Burro"},{"Spawn"},{"Plagu"},{"Consu"},{"Ensna"},{"LAspc"},
	{"Carap"},{"FCarp"},{"Melee"},{"Missl"},{"FAtta"},{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},
	{"NULL!"},{"NULL!"},{"NULL!"},{"NULL!"},{"Cancl"},{"Extra"},{">>Gas"},{">>Min"}
	}
};	

