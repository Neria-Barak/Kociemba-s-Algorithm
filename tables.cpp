// BeginPackage["TwoPhase`", {"Combinatorica`"}]

// (* Define basic face turns for corners and edges *)
// cU = {{4, 1, 2, 3, 5, 6, 7, 8}, {0, 0, 0, 0, 0, 0, 0, 0}};
// cR = {{5, 2, 3, 1, 8, 6, 7, 4}, {2, 0, 0, 1, 1, 0, 0, 2}};
// cF = {{2, 6, 3, 4, 1, 5, 7, 8}, {1, 2, 0, 0, 2, 1, 0, 0}};
// cD = {{1, 2, 3, 4, 6, 7, 8, 5}, {0, 0, 0, 0, 0, 0, 0, 0}};
// cL = {{1, 3, 7, 4, 5, 2, 6, 8}, {0, 1, 2, 0, 0, 2, 1, 0}};
// cB = {{1, 2, 4, 8, 5, 6, 3, 7}, {0, 0, 1, 2, 0, 0, 2, 1}};

// eU = {{4, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
// eR = {{9, 2, 3, 4, 12, 6, 7, 8, 5, 10, 11, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
// eF = {{1, 10, 3, 4, 5, 9, 7, 8, 2, 6, 11, 12}, {0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0}};
// eD = {{1, 2, 3, 4, 6, 7, 8, 5, 9, 10, 11, 12}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
// eL = {{1, 2, 11, 4, 5, 6, 10, 8, 9, 3, 7, 12}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
// eB = {{1, 2, 3, 12, 5, 6, 7, 11, 9, 10, 4, 8}, {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1}};

// (* Identity permutations *)
// cId = {Range[8], ConstantArray[0, 8]};
// eId = {Range[12], ConstantArray[0, 12]};

// (* Multiplication functions for corners and edges *)
// cornMult[x_, y_] := Module[{z, oa, ob},
//    {
//     Table[x[[1, y[[1, z]]]], {z, 8}],
//     Table[
//      oa = x[[2, y[[1, z]]]];
//      ob = y[[2, z]];
//      If[oa < 3,
//       If[ob < 3,
//        Mod[oa + ob, 3], (* Main case *)
//        Mod[oa + ob, 3] + 3
//        ],
//       If[ob < 3,
//        Mod[oa - ob, 3] + 3,
//        Mod[oa - ob, 3]
//        ]
//       ], {z, 8}]
//     }
//    ];

// edgeMult[x_, y_] := Module[{z, oa, ob},
//    {
//     Table[x[[1, y[[1, z]]]], {z, 12}],
//     Table[
//      oa = x[[2, y[[1, z]]]];
//      ob = y[[2, z]];
//      Mod[oa + ob, 2], {z, 12}]
//     }
//    ];

// multSequence[x__] /; (Count[{x}[[1, 2]], _Integer] == 8) :=
//  Module[{}, Fold[cornMult, cId, {x}]]

// multSequence[x__] /; (Count[{x}[[1, 2]], _Integer] == 12) :=
//  Module[{}, Fold[edgeMult, eId, {x}]]

// CircleDot[x__] := Module[{c, e},
//    c = Fold[cornMult, cId, {x}[[All, 1]]];
//    e = Fold[edgeMult, eId, {x}[[All, 2]]];
//    {c, e}
//    ];

// (* Coordinate functions *)
// flip[o_] := FromDigits[Mod[Most[o], 2], 2]
// invFlip[n_] := Module[{d}, d = IntegerDigits[n + 2048, 2]; Rest[Append[d, Mod[Total[d] + 1, 2]]]] - EO

// twist[o_] := FromDigits[Mod[Most[o], 3], 3]
// invTwist[n_] := Module[{d}, d = IntegerDigits[n + 2187, 3]; Rest[Append[d, Mod[4 - Total[d], 3]]]] - CO

// slice[p_] := 494 - (RankKSubset[Sort[Take[InversePermutation[p], -4]], Range[12]]);
// invSlice[n_] := Module[{s, r, i, x},
//    s = UnrankKSubset[494 - n, 4, Range[12]];
//    r = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//    Do[r[[s[[i]]]] = 8 + i, {i, 4}];
//    x = 1;
//    Do[If[r[[i]] == 0, r[[i]] = x++], {i, 12}];
//    r
//    ];

// corner[p_] := RankPermutation[p];
// invCorner[n_] := UnrankPermutation[n, 8]; - CP

// edge8[p_] := Module[{t},
//    t = Take[p, 8];
//    If[PermutationQ[t],
//     RankPermutation[t],
//     -1
//     ]
//    ];

// invEdge8[n_] := Join[UnrankPermutation[n, 8], {9, 10, 11, 12}]; - EP8

// edge4[p_] := Module[{t}, - EP4
//    t = Take[p, -4] - 8;
//    If[PermutationQ[t],
//     RankPermutation[t],
//     -1
//     ]
//    ];

// invEdge4[n_] := Join[Range[8], UnrankPermutation[n, 4] + 8];

// (* Move table generation function *)
// moveTable[name_, cornerQ_, permQ_, coord_, invCoord_, size_] :=
//   Module[{f, d, cubies, j, t},
//    SetDirectory[NotebookDirectory[]];
//    If[FileExistsQ[name],
//     Print["Loading ", name, " Table"];
//     t = Get[name],
//     Print["Building ", name, " Table"];
//     cubies = If[cornerQ, 8, 12];
//     d = If[permQ, Array[0 &, cubies], Array[# &, cubies]];
//     f[move_, i_] :=
//      If[permQ,
//       coord /@ Flatten[
//           Rest[NestList[multSequence[#, move] &, {invCoord[i], d}, 3]],
//           1][[1 ;; 5 ;; 2]],
//       coord /@ Flatten[
//           Rest[NestList[multSequence[#, move] &, {d, invCoord[i]}, 3]],
//           1][[2 ;; 6 ;; 2]]
//       ];
//     t = Table[
//       If[Mod[j, 1000] == 0, Print[j, "/", size]];
//       If[cornerQ,
//        Join[f[cU, j], f[cR, j], f[cF, j], f[cD, j], f[cL, j], f[cB, j]],
//        Join[f[eU, j], f[eR, j], f[eF, j], f[eD, j], f[eL, j], f[eB, j]]
//        ], {j, 0, size - 1}];
//     Put[t, name];
//     ResetDirectory[];
//     t
//     ]
//    ];

// (* Generate move tables *)
// flipMove = moveTable["flipMove", False, False, flip, invFlip, 2048];
// twistMove = moveTable["twistMove", True, False, twist, invTwist, 2187];
// sliceMove = moveTable["sliceMove", False, True, slice, invSlice, 495];

// cornerMove = moveTable["cornerMove", True, True, corner, invCorner, 40320];
// edge4Move = moveTable["edge4Move", False, True, edge4, invEdge4, 24];
// edge8Move = moveTable["edge8Move", False, True, edge8, invEdge8, 40320];

// EndPackage[]


// RankPermutation[p_List] := 
//   Module[{n = Length[p], rank = 0, perm = p, i},
//    For[i = 1, i <= n, i++,
//     rank += Position[Sort[perm[[i ;;]]], perm[[i]]][[1, 1]] - 1;
//     perm = DeleteCases[perm, perm[[i]], {i}]
//     ];
//    rank
//    ];