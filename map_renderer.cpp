#include "map_renderer.h"
#include <iostream>

#define ANSI_RESET   "\033[0m"
#define ANSI_RED     "\033[31m"
#define ANSI_GREEN   "\033[32m"
#define ANSI_WHITE   "\033[37m"
#define ANSI_DIM     "\033[2m"

static std::vector<std::string> s_templateLines = {
    "┌─────────────────────────────────────────────────────────────────────────────────────────┐",
    "│                                     KAART VAN ARALUEN                                   │",
    "├─────────────────────────────────────────────────────────────────────────────────────────┤",
    "│                                                                                         │",
    "│   ┌─────────────────┐                                                                   │",
    "│   │     PICTA       │                                                                   │",
    "│   │    (NOORDEN)    │                                                                   │",
    "│   │ Drowned_Forest  │                                                                   │",
    "│   └─────────────────┘                                                                   │",
    "│                                                                                         │",
    "│  ┌─────────┐        ┌────────────────────────────────────────────────────┐              │",
    "│  │         │        │                  ARALUEN                           │              │",
    "│  │HIBERNIA │        │                 (CENTRAAL)                         │              │",
    "│  │         │        │  Norgate                    Caraway                │              │",
    "│  └─────────┘        │Forest(Araluen)  Araluen     Hackham                │              │",
    "│                     │  Redmont      Gorlan                               │              │",
    "│                     │                           Thomtree  Seacliff       │              │",
    "│                     │Western_World   Mountains   Uthal_Plain   The_Fens  │              │",
    "│                     │         Solitary Plain   3 Step Pass (Araluen)     │              │",
    "│                     └────────────────────────────────────────────────────┘              │",
    "│                                                                                         │",
    "│   ┌──────────────────────┐                              ┌──────────────────────┐        │",
    "│   │     CELTICA          │                              │  MORGARATH'S         │        │",
    "│   │   (ZUIDWEST)         │                              │    PLATEAU           │        │",
    "│   │   Villages           │                              │3 Step Pass (Plateau) │        │",
    "│   │3 Step Pass (Celtica) │                              │ Mountains (Plateau)  │        │",
    "│   └──────────────────────┘                              │  South Cliffs        │        │",
    "│                                                         └──────────────────────┘        │",
    "│                                                                                         │",
    "│                                       N                                                 │",
    "│                                       ↑                                                 │",
    "│                                 W ←   +   → E                                           │",
    "│                                       ↓                                                 │",
    "│                                       S                                                 │",
    "└─────────────────────────────────────────────────────────────────────────────────────────┘"
};

static std::unordered_map<std::string, Location> s_nodes = {
    {"picta", {"picta","PICTA", true,false,false,"PICTA region",0}},
    {"hibernia", {"hibernia","HIBERNIA", true,false,false,"HIBERNIA region",0}},
    {"araluen", {"araluen","Araluen", true,false,false,"Araluen central",0}},
    {"norgate", {"norgate","Norgate", true,false,false,"Norgate town",1}},
    {"caraway", {"caraway","Caraway", true,false,false,"Caraway hamlet",0}},
    {"forest_araluen", {"forest_araluen","Forest(Araluen)", true,false,false,"Forest near Araluen",0}},
    {"redmont", {"redmont","Redmont", true,false,false,"Redmont village",2}},
    {"gorlan", {"gorlan","Gorlan", true,false,false,"Gorlan region",0}},
    {"thomtree", {"thomtree","Thomtree", true,false,false,"Thomtree area",0}},
    {"seacliff", {"seacliff","Seacliff", true,false,false,"Seacliff area",0}},
    {"western_world", {"western_world","Western_World", true,false,false,"Western World",0}},
    {"mountains", {"mountains","Mountains", true,false,false,"Mountain range",0}},
    {"uthal_plain", {"uthal_plain","Uthal_Plain", true,false,false,"Uthal Plain",0}},
    {"the_fens", {"the_fens","The_Fens", true,false,false,"The Fens",0}},
    {"solitary_plain", {"solitary_plain","Solitary Plain", true,false,false,"Solitary Plain",0}},
    {"three_step_araluen", {"three_step_araluen","3 Step Pass (Araluen)", true,false,false,"Pass",0}},
    {"celtica", {"celtica","CELTICA", true,false,false,"CELTICA",0}},
    {"villages", {"villages","Villages", true,false,false,"Villages area",0}},
    {"three_step_celtica", {"three_step_celtica","3 Step Pass (Celtica)", true,false,false,"Celtica pass",0}},
    {"morg_plateau", {"morg_plateau","MORGARATH'S", true,false,false,"Morgarath's Plateau",0}},
    {"plateau_pass", {"plateau_pass","3 Step Pass (Plateau)", true,false,false,"Plateau pass",0}},
    {"plateau_mountains", {"plateau_mountains","Mountains (Plateau)", true,false,false,"Plateau mountains",0}},
    {"south_cliffs", {"south_cliffs","South Cliffs", true,false,false,"South Cliffs",3}},
    {"drowned_forest", {"drowned_forest","Drowned_Forest", true,false,false,"Drowned Forest",0}},
    };

static bool replaceFirst(std::string &s, const std::string &from, const std::string &to) {
    size_t pos = s.find(from);
    if (pos == std::string::npos) return false;
    s.replace(pos, from.size(), to);
    return true;
}

void printFullMapWithMarkers(const std::unordered_map<std::string, Location>& nodes,
                             const std::vector<std::string>& tpl,
                             bool showUnexplored)
{
    std::vector<std::string> lines = tpl;
    for (const auto& kv : nodes) {
        const Location& loc = kv.second;
        if (!showUnexplored && !loc.explored) continue;
        std::string left = loc.current ? "-> " : "   ";
        std::string right = loc.defeated ? " X" : "  ";
        std::string repl = left + loc.label + right;
        for (auto &line : lines) {
            if (line.find(loc.label) != std::string::npos) { replaceFirst(line, loc.label, repl); break; }
        }
    }
    for (const auto &L : lines) std::cout << L << "\n";
    std::cout << "\nLegenda: 'X' = verslagen locatie. '->' = huidige locatie.\n";
}

static std::string renderColoredLabel(const Location& loc) {
    std::string text = loc.label;
    if (loc.current) return std::string(ANSI_GREEN) + "-> " + text + ANSI_RESET;
    if (loc.defeated) return std::string(ANSI_RED) + text + " X" + ANSI_RESET;
    if (loc.explored) return std::string(ANSI_WHITE) + text + ANSI_RESET;
    return std::string(ANSI_DIM) + text + ANSI_RESET;
}

void printFullMapWithMarkersColored(const std::unordered_map<std::string, Location>& nodes,
                                    const std::vector<std::string>& tpl,
                                    bool showUnexplored)
{
    std::vector<std::string> lines = tpl;
    for (auto &line : lines) {
        for (const auto& kv : nodes) {
            const Location& loc = kv.second;
            if (!showUnexplored && !loc.explored) continue;
            size_t pos = line.find(loc.label);
            if (pos != std::string::npos) {
                std::string colored = renderColoredLabel(loc);
                line.replace(pos, loc.label.size(), colored);
            }
        }
    }
    for (const auto &L : lines) std::cout << L << "\n";
    std::cout << "\nLegenda: " << ANSI_GREEN << "-> current" << ANSI_RESET
              << "  " << ANSI_RED << "X defeated" << ANSI_RESET
              << "  " << ANSI_WHITE << "explored" << ANSI_RESET
              << "  " << ANSI_DIM << "unexplored" << ANSI_RESET << "\n";
}

std::vector<std::string> validateTemplateAgainstNodes(const std::vector<std::string>& tpl,
                                                      const std::unordered_map<std::string, Location>& nodes)
{
    std::vector<std::string> missing;
    std::string joined;
    for (const auto &l : tpl) joined += l + "\n";
    for (const auto &kv : nodes) {
        const std::string &label = kv.second.label;
        if (joined.find(label) == std::string::npos) missing.push_back(label);
    }
    return missing;
}

const std::vector<std::string>& getTemplateLines(){ return s_templateLines; }
std::unordered_map<std::string, Location> getDefaultNodesCopy(){ return s_nodes; }
