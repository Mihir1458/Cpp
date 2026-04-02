 for (int i = 0; i < k; i++)
    {
        string fuel, name, mdl;
        double prc;
        cout << "Enter fuel type: ";
        cin >> fuel;
        cout << "Enter brand name: ";
        cin >> name;
        cout << "Enter model: ";
        cin >> mdl;
        cout << "Enter price: ";
        cin >> prc;
        car temp(fuel, name, mdl, prc);
        c1[i] = temp;
    }