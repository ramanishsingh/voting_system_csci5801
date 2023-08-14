all: 
	g++ audit_UT.cpp irv_UT.cpp irv_ballot_UT.cpp irv_candidate_UT.cpp oplv_candidate_UT.cpp oplv_party_UT.cpp oplv_UT.cpp main_UT.cpp po_candidate_UT.cpp po_UT.cpp -o unittest -lgtest_main -lgtest -lgmock -Wl,-rpath,/lib  -pthread

maintest:
	g++ main_UT.cpp -o maintest -lgtest_main -lgtest -lgmock -Wl,-rpath,/lib  -pthread

clean:
	rm unittest maintest