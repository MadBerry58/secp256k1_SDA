auto intervals = 18051648; // 0x1137240
char I_k[] = "EDED35E2DD180B3069CABD39C376B4D874708B552E18F3861D0FBB5F5D";
char I_x[] = "4d5ccdf43771c81a609bae495080886c7fe130c075982e9ea249f3930e619cc2";
char I_y[] = "54da63392c132035d1530469a449f4b383016c5846266e9d7ff7e67e42efe7e7";

auto subIntervals = 12; // 0xC
char sI_k[] = "13D3C47D926CAB995E263A6F7AF48F1209B40B9C6E82144B2D16A4F29D";
char nsI_k[] = "FFFFFFEC2C3B826D935466A1D9C59083C61FCADCFB3D03CD3DBE135FB9914EA4";
char sI_x[] = "ae4252d8c002f5ad3f49254a8031809ebfea77efe98573263a2272aac2c9eda7";
char sI_y[] = "9268c32d7351167ad4e9c30d89579b21668c96044418974ec812660dfa90d985";
char nsI_y[] = "6d973cd28caee9852b163cf276a864de997369fbbbe768b137ed99f1056f22aa";

auto jumps = 7058; // 7058 = 0x1B92 , 2* 7058 = 0x3724
char kJ[] = "5C0D2392F0EC680CBBD9E31E72D8033A92767425B1D6705A306EEF";
char nkJ[] = "FFFFFFFFFFA3F2DC6D0F1397F344261B9C3C04E374B629C79A20881C7605D252";
char xJ[] = "7a3e3a50b0b8a8167fb8e271f6d7636b6d328fcd9a19dd4f3dc7935b10e44e2d";
char yJ[] = "17ec64bd587820ff7f2b830a3403a061c58f89f1a7d07f64ea9274db8b8a72ff";
char nyJ[] = "e8139b42a787df0080d47cf5cbfc5f9e3a70760e582f809b156d8b2374758930";

char kJ2[] = "FFFFFFF6161DC136C9AA3350ECE2C841406753E1D542D2047EC838F644E3C7F4";
char nkJ2[] = "9E9E23EC93655CCAF131D37BD7A478904DA05CE37410A25968B52794D";
char xJ2[] = "aea9d03ff30f72eb9efb5b6787e1ffa9970fa76e24f5485a7874ea689ec7cfd4";
char yJ2[] = "b0cfbd70128d1ed877da292de2eaae1033b59dcbee53f586436543354958e9f";
char nyJ2[] = "f4f30428fed72e1278825d6d21d1551efcc4a623411ac0a79bc9abcbab6a6d90";

auto subJumps = 18522; // 0x485A
char ksJ[] = "145B4081CC2E32B538FE828E3D0E59728A42D47EC1F61721CB3";
char xsJ[] = "3f20f070b21dc3d8502c2bc963d072fe3a4f6499983e281a425043f1188fc443";
char ysJ[] = "88728e6a46fc44c9a3aaf6f08f7f62626a58ed30de614afb75c903ab15c5a652";

int generatePointsFile_old(std::ofstream cardinalLSB_write, std::set<unsigned long> LSBset, Point G, Point I, Point sI, Point J, Point sJ, Point A, int intervals, int subIntervals)
{
    bool *listLoaded;
    cardinalLSB_write.open("cardinalLSB");
    LSBset.insert(G.getLSB());
    cardinalLSB_write << G.getLSB() << "\n";
    LSBset.insert(I.getLSB());
    cardinalLSB_write << I.getLSB() << "\n";
    LSBset.insert(sI.getLSB());
    cardinalLSB_write << sI.getLSB() << "\n";
    LSBset.insert(J.getLSB());
    cardinalLSB_write << J.getLSB() << "\n";
    LSBset.insert(sJ.getLSB());
    cardinalLSB_write << sJ.getLSB() << "\n";
    char user_input = 's';
    // TODO: create a filename generator to output multiple files.

    std::cout << "The list needs 2.5GB of disk space and will take a good while. Are you sure?(Y/n)\n";
    std::cin >> user_input;
    if (user_input == 'Y')
    {
        std::cout << "Generating new LSB file\n";
        /// TODO: Generate cardinal Points function
        std::cout << "Cardinal point file generated\n";
        // std::cout << "Elements in set: "<< LSB_cardinal.size() << "\n";
        *listLoaded = true;
    }
    else
    {
        std::cout << "Exiting to menu\n";
    }

    for (int i = 0; i < intervals / 2; ++i)
    {
        for (int j = 0; j < subIntervals; ++j)
        {
            A.addPoint(A, sI);
            LSBset.insert(A.getLSB());
            cardinalLSB_write << A.getLSB() << "\n";
        }
        A.addPoint(A, G);
        LSBset.insert(A.getLSB());
        cardinalLSB_write << A.getLSB() << "\n";
    }
    cardinalLSB_write.close();
    return 0;
}
