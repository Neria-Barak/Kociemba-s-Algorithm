#include "moves.hpp"

using namespace std;

array<array<int, N_MOVE>, N_FLIP> eoMoveTable;
void createEOMoveTable() {

    CubieCube* c = new CubieCube();
    for (int i = 0; i < N_FLIP; i++) {
        c->InverseEP(i);
        for (int j = U1M; j <= B3M; j++) {
            c->move(j);
            eoMoveTable[i][j] = c->getEPCoord();
        }
    }
}

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

int main() {
    cout << "hey" << endl;

    // Create CO move table
    createEOMoveTable();

    cout << "hey" << endl;

    // Open binary file for writing
    ofstream outFile("epMoveTable.bin", ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return 1;
    }

    // Write the entire std::array to the binary file
    outFile.write(reinterpret_cast<const char*>(eoMoveTable.data()), N_FLIP * N_MOVE * sizeof(int));

    outFile.close();
    cout << "cpMoveTable successfully written to cpMoveTable.bin" << endl;

    return 0;
}