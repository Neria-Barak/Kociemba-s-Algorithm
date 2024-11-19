#include "moves.hpp"

using namespace std;
// cp co eo

//TODO:
// TwistMove: array[0..2187-1,Ux1..Fsx3] of Word;              - DONE
// FlipMove: array[0..2048-1,Ux1..Fsx3] of Word;               - DONE
// UDSliceMove: array[0..495-1,Ux1..Fsx3] of Word;             - TODO
// CentOriMove: array[0..4096-1,Ux1..Fsx3] of Word;

// CentOriRFLBMod2Move: array[0..16-1,Ux1..Fsx3] of Word;
// TetraMove: array[0..70-1,Ux1..Fsx3] of Word;
// CornPermMove: array[0..40320-1,Ux1..Fsx3] of Word;          - DONE
// UDSliceSortedMove: array[0..11880-1,Ux1..Fsx3] of Word;     - TODO
// UDSliceSortedSymMove: array[0..788-1,Ux1..Fsx3] of Integer;
// Edge8PermMove: array[0..40320-1,Ux1..Fsx3] of Word;         - TODO


// array<array<int, N_MOVE>, 2048> eoMoveTable;
// void generateEOMoveTable() {
//     CubieCube* c = new CubieCube();
//     for (int i = 0; i < 2048; i++) {
//         c->InvEO(i);
//         for (int j = U1M; j <= B3M; j++) {
//             c->move(j);
//             eoMoveTable[i][j] = c->getEOCoord();
//         }
//     }
// }

array<array<int, N_MOVE>, N_TWIST> coMoveTable2;
void generateCOMoveTable() {
    CubieCube* c = new CubieCube();
    for (int i = 0; i < N_TWIST; i++) {
        c->InvCO(i);
        for (int j = U1M; j <= B3M; j++) {
            c->move(j);
            coMoveTable2[i][j] = c->getCOCoord();
            c->move(inv_move[j]);
        }
    }
}

array<array<int, N_MOVE>, N_CORNERS_PERM> cpMoveTable2;
void generateCPMoveTable() {
    CubieCube* c = new CubieCube();
    for (int i = 0; i < N_CORNERS_PERM; i++) {
        c->InvCP(i);
        for (int j = U1M; j <= B3M; j++) {
            c->move(j);
            cpMoveTable2[i][j] = c->getCPCoord();
            c->move(inv_move[j]);
        }
    }
}

// array<array<int, N_MOVE>, N_FLIP> eoMoveTable;
// void createEPMoveTable() {
//     CubieCube* c = new CubieCube();
//     for (int i = 0; i < N_FLIP; i++) {
//         c->InvEP(i);
//         for (int j = U1M; j <= B3M; j++) {
//             c->move(j);
//             eoMoveTable[i][j] = c->getEPCoord();
//         }
//     }
// }

//+++++++++++++Create Move Table for the UDSliceSorted raw-coordinate+++++++++++
// procedure CreateUDSliceSortedMoveTable;
// var c: CubieCube; i,k: Integer; j: TurnAxis;
// begin
//   c:= CubieCube.Create;
//   for i:=0 to 11879 do
//   begin
//     if i and $fff = 0 then Application.ProcessMessages;
//     c.InvUDSliceSortedCoord(i);
//     for j:= U to Fs do
//     begin
//       for k:= 0 to 3 do
//       begin
//         c.Move(j);
//         if k<>3 then UDSliceSortedMove[i,Move(3*Ord(j)+k)]:=c.UDSliceSortedCoord;
//       end;
//     end;
//   end;
//   c.Free;
//   Form1.ProgressBar.Position:=50;
// end;

// procedure CubieCube.InvUDSliceSortedCoord(w: Word);
// var x: Word; order: array[0..3] of Integer; used: array[FR..BR] of Boolean;
//     j,k,e: Edge; i,m: Integer;
// begin
//   x:= w mod 24;
//   InvUDSliceCoord(w div 24);

//   for j:= FR to BR do used[j]:=false;
//   for i:= 0 to 3 do
//   begin
//     order[i]:= x mod (i+1);
//     x:= x div (i+1);
//   end;

//   for i:= 3 downto 0 do
//   begin
//     k:=BR; while used[k] do Dec(k);
//     while order[i]>0 do
//     begin
//       Dec(order[i]);
//       repeat
//        Dec(k);
//       until not used[k];
//     end;

//     m:=-1;
//     for j:= UR to BR do //search the i. UD-slice edge
//     begin
//       e:= PEdge^[j].e;
//       if (e=FR) or (e=FL) or (e=BL) or (e=BR) then Inc(m);
//       if m=i then
//       begin
//         PEdge^[j].e:=k;
//         used[k]:=true;
//         break;
//       end;
//     end;
//   end;
// end;

void writeTable() {
    generateCPMoveTable();

    ofstream outFile("MoveTables/cpMoveTable.bin", ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(cpMoveTable2.data()), N_CORNERS_PERM * N_MOVE * sizeof(int));
    
    if (!outFile) {  // Verify that the write operation was successful
        cerr << "Error writing to file." << endl;
    } else {
        cout << "cpMoveTable successfully written to cpMoveTable.bin" << endl;
    }

    outFile.close();
}