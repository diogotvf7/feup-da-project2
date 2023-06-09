#include "../headers/Menu.h"

using namespace std;

Menu::Menu(const vector<string> &paths) {
    for (auto &path : paths)
        graphs.emplace(path, nullptr);
    headers = {"", "Backtracking", "Triangular Approximation", "Ant Colony Approximation"};
}

void Menu::readGraph(const string &path) {
    auto g = find(cachedGraphs.begin(), cachedGraphs.end(), path);
    if (g == cachedGraphs.end()) {
        Graph *graph = new Graph();
        if (path.substr(0, path.find('/')) == "real-graphs") {
            csv::readNodes(path + "nodes.csv", graph);
            csv::readEdges(path + "edges.csv", graph);
        } else if (path.substr(0, path.find('/')) == "extra-graphs")
            csv::readEdges(path, graph, false, false);
        else if (path.substr(path.find_last_of('/'), path.size()) == "tourism.csv")
            csv::readEdges(path, graph, true, true);
        else csv::readEdges(path, graph);
        graphs[path] = graph;
    }
    updateCache(path);
}

void Menu::updateCache(const string &path) {
    auto rm = find(cachedGraphs.begin(), cachedGraphs.end(), path);
    if (rm != cachedGraphs.end())
        cachedGraphs.erase(rm); // remove graph from its position in cache
    if (cachedGraphs.size() == 3) {
        delete graphs[cachedGraphs[0]]; // delete graph memory
        cachedGraphs.erase(cachedGraphs.begin()); // remove graph from cache
    }
    cachedGraphs.push_back(path); // add graph to cache
}

void Menu::init() {
    while (true) {
        cleanTerminal();
        cout << '|' << string(100, '-') << '|' << endl
                  << '|' <<  center("Welcome to the TSP solver!", 100) << '|' <<  endl
                  << '|' << center("Please select an option:", 100) << '|' << endl
                  << '|' << string(100, '-') << '|' << endl
                  << '|' << center("1.  Solve TSP using backtracking", 100) << '|' << endl
                  << '|' << center("2.  Solve TSP using triangular approximation heuristic", 100) << '|' << endl
                  << '|' << center("3.  Solve TSP using Ant Colony Optimization", 100) << '|' << endl
                  << '|' << center("4.  Exit", 100) << '|' << endl
                  << '|' << string(100, '-') << '|' << endl
                  << setw(20) << right << "Option: ";
        cin >> input;
        switch (stoi(input)) {
            case 1:
                selectGraph(1);
                break;
            case 2:
                selectGraph(2);
                break;
            case 3:
                selectGraph(3);
                break;
            case 4:
                return;
            default:
                cout << "Invalid option!" << endl;
                break;
        }
    }
}

bool Menu::selectGraph(const int headerIdx) {
    vector<string> options;
    bool alive = true;
    while (alive) {
        int i = 1;
        cleanTerminal();
        cout << '|' << string(100, '-') << '|' << endl
                  << '|' << center(headers[headerIdx], 100) << '|' << endl
                  << '|' << center("Please select a graph to solve:", 100) << '|' << endl
                  << '|' << string(100, ' ') << '|' << endl
                  << '|' << string(100, '-') << '|' << endl;


        std::regex pattern;
        if (headerIdx == 1) pattern = regex("^toy-graphs/");
        else if (headerIdx == 2) pattern = regex("^(extra-graphs/|real-graphs/|toy-graphs/tourism.csv|toy-graphs/stadiums.csv)");
        else if (headerIdx == 3) pattern = regex("^(?!.*\\/shipping\\.csv).*$");
        for (auto &graph : graphs) {
            if (regex_search(graph.first,pattern)) {
                options.push_back(graph.first);
                cout << right << setw(25) << ' ' << to_string(i++) + "." << setw(3) << ' ' << graph.first << endl;
            }
        }

        cout << '|' << right << setw(24) << ' ' << "0.   Exit" << endl
                   << '|' << string(100, ' ') << '|' << endl
                   << '|' << string(100, '-') << '|' << endl
                   << right << setw(20) << "Option: ";
        cin >> input;
        switch (stoi(input)) {
            case 0:
                alive = false;
                break;
            default:
                readGraph(options[stoi(input) - 1]);
                alive = displayInfo(headerIdx, options[stoi(input) - 1]);
                options.clear();
                break;
        }
    }
    return false;
}

bool Menu::displayInfo(const int headerIdx, const string &path) {
    /*vector<int> res;*/
    Path res, res2 = {{-1}, -1};
    double elapsedTime, elapsedTime2, initialPheromones = 0.03, evaporationRate = 0.1, pheromoneDeposit = 1, enhancement2Opt;
    int numIterations = 75, numAnts = 10, ALPHA = 1, BETA = 1, iterations2Opt = -1;
    vector<vector<double>> distanceCache(graphs[path]->getNodes().size(), vector<double>(graphs[path]->getNodes().size(), -1));

    if (headerIdx == 1)
        res = measureExecutionTime(elapsedTime, *graphs[path], &Graph::tspBacktracking);
    else if (headerIdx == 2)
        res = measureExecutionTime(elapsedTime, *graphs[path], &Graph::approxTSPTour);
    else if (headerIdx == 3) {
        chooseACOParams(initialPheromones, evaporationRate, pheromoneDeposit, numIterations, numAnts, ALPHA, BETA);
        vector<vector<double>> pheromoneTrails(graphs[path]->getNodes().size(), vector<double>(graphs[path]->getNodes().size(), initialPheromones));
        res = measureExecutionTime(elapsedTime, *graphs[path], &Graph::aco, pheromoneTrails, evaporationRate, pheromoneDeposit, numIterations, numAnts, ALPHA, BETA, distanceCache);
    }

    cout << fixed << setprecision(0);
    bool alive = true;
    while (alive) {
        cleanTerminal();
        cout << '|' << string(100, '-') << '|' << endl
             << '|' << center(headers[headerIdx] + " for " + path, 100) << '|' << endl
             << '|' << string(100, ' ') << '|' << endl
             << '|' << string(100, '-') << '|' << endl
             << '|' << string(100, ' ') << '|' << endl
             << '|' << center(headers[headerIdx] + " execution time: " + to_string(elapsedTime) + " ms", 100) << '|' << endl
             << '|' << center("Distance: " + to_string(res.distance), 100) << '|' << endl;
        if (res2.distance != -1)
            cout << '|' << string(100, ' ') << '|' << endl
                 << '|' << center("2-opt execution time: " + to_string(elapsedTime2) + " ms", 100) << '|' << endl
                 << "|" << center("Distance after 2-opt : " + to_string(res2.distance), 100) << '|' << endl
                 << "|" << center("2-opt enhancement: " + to_string(enhancement2Opt * 100) + "%", 100) << '|' << endl;
        cout << '|' << string(100, ' ') << '|' << endl
             << '|' << string(100, '-') << '|' << endl
             << '|' << string(100, ' ') << '|' << endl;
        if (res2.distance != -1)
            cout << '|'  << center("0. Show nodes after 2-opt", 100) << '|' << endl;
        cout << '|' << center("1.  Show nodes", 100) << '|' << endl
             << '|' << center("2.  Apply 2-opt", 100) << '|' << endl
             << '|' << center("3.  Back", 100) << '|' << endl
             << '|' << center("4.  Menu", 100) << '|' << endl
             << '|' << string(100, '-') << '|' << endl
             << right << setw(20) << "Option: ";
        cin >> input;
        switch (stoi(input)) {
            case 1:
                alive = displayPath(res, path, headerIdx);
                break;
            case 2:
                cout << "Number of iterations (-1 for max iterations): ";
                cin >> iterations2Opt;
                res2 = res;
                enhancement2Opt = measureExecutionTime(elapsedTime2, *graphs[path], &Graph::apply2OptSwap, res2, distanceCache, iterations2Opt);
                break;
            case 3:
                return true;
            case 4:
                return false;
            case 0:
                if (res2.distance != -1) {
                    alive = displayPath(res2, path, headerIdx);
                    break;
                }
            default:
                cout << "Invalid option!" << endl;
                cin >> input;
                break;
        }
    }
    return false;
}

void Menu::chooseACOParams(double &initialPheromones, double &evaporationRate, double &pheromoneDeposit, int &numIterations,
                           int &numAnts, int &ALPHA, int &BETA) {
    cout << fixed << setprecision(0);
    bool alive = true;
    while (alive) {
        cleanTerminal();
        cout << '|' << string(100, '-') << '|' << endl
                  << '|' << center("ACO parameters", 100) << '|' << endl
                  << '|' << string(100, ' ') << '|' << endl
                  << '|' << string(100, '-') << '|' << endl
                  << '|' << string(100, ' ') << '|' << endl
                  << '|' << center("1.  Initial pheromones: " + to_string(initialPheromones), 100) << '|' << endl
                  << '|' << center("2.  Evaporation rate: " + to_string(evaporationRate), 100) << '|' << endl
                  << '|' << center("3.  Pheromone deposit: " + to_string(pheromoneDeposit), 100) << '|' << endl
                  << '|' << center("4.  Number of iterations: " + to_string(numIterations), 100) << '|' << endl
                  << '|' << center("5.  Number of ants: " + to_string(numAnts), 100) << '|' << endl
                  << '|' << center("6.  ALPHA: " + to_string(ALPHA), 100) << '|' << endl
                  << '|' << center("7.  BETA: " + to_string(BETA), 100) << '|' << endl
                  << '|' << string(100, '-') << '|' << endl
                  << '|' << string(100, ' ') << '|' << endl
                  << '|' << center("0.  Save", 100) << '|' << endl
                  << '|' << string(100, '-') << '|' << endl
                  << right << setw(20) << "Option: ";
        cin >> input;
        switch (stoi(input)) {
            case 0:
                return;
            case 1:
                cout << "Initial pheromones: ";
                cin >> input;
                initialPheromones = stod(input);
                break;
            case 2:
                cout << "Evaporation rate: ";
                cin >> input;
                evaporationRate = stod(input);
                break;
            case 3:
                cout << "Pheromone deposit: ";
                cin >> input;
                pheromoneDeposit = stod(input);
                break;
            case 4:
                cout << "Number of iterations: ";
                cin >> input;
                numIterations = stoi(input);
                break;
            case 5:
                cout << "Number of ants: ";
                cin >> input;
                numAnts = stoi(input);
                break;
            case 6:
                cout << "ALPHA: ";
                cin >> input;
                ALPHA = stoi(input);
                break;
            case 7:
                cout << "BETA: ";
                cin >> input;
                BETA = stoi(input);
                break;
            default:
                cout << "Invalid option!" << endl;
                break;
        }
    }
}

bool Menu::displayPath(const Path &path, const string &graphPath, int headerIdx) {
    while (true) {
        cleanTerminal();
        cout << fixed << setprecision(0);
        cout << '|' << string(100, '-') << '|' << endl
             << '|' << center("Path for " + headers[headerIdx] + " for graph: " + graphPath, 100) << '|' << endl
             << '|' << string(100, ' ') << '|' << endl
             << '|' << string(100, '-') << '|' << endl
             << '|' << string(100, ' ') << '|' << endl
             << setw(11) << left << "|";
        for (int i = 0; i < path.nodes.size(); ++i) {
            cout << setw(5) << left << path.nodes[i];
            if (i != path.nodes.size() - 1) cout << "-> ";
            else cout << string(8 * (10 - path.nodes.size() % 10) + 13, ' ') << '|';
            if ((i + 1) % 10 == 0 && i != 0) {
                cout << setw(11) << right << "|" << endl
                     << setw(11) << left << "|";
            }
        }
        cout << endl
             << '|' << string(100, '-') << '|' << endl
             << '|' << center("Distance: " + to_string(path.distance), 100) << '|' << endl
             << '|' << string(100, '-') << '|' << endl
             << '|' << string(100, ' ') << '|' << endl
             << '|' << center("1.  Back", 100) << '|' << endl
             << '|' << center("2.  Menu", 100) << '|' << endl
             << '|' << string(100, '-') << '|' << endl
             << right << setw(20) << "Option: ";
        cin >> input;
        while (true) {
            switch (stoi(input)) {
                case 1:
                    return true;
                case 2:
                    return false;
                default:
                    cout << "Invalid option!" << endl;
                    cin >> input;
                    break;
            }
        }
    }
}

string Menu::center(const string &str, int width) {
    int padding = width - (int) str.size();
    int leftPadding = padding / 2;
    int rightPadding = padding - leftPadding;
    return string(leftPadding, ' ') + str + string(rightPadding, ' ');
}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

