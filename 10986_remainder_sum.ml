let read_pair () =
  let input = read_line () in
  Scanf.sscanf input "%d %d" (fun x y -> x, y)
;;

let nC2 n = n * (n - 1) / 2

let () =
  let _n, m = read_pair () in
  let lst = String.split_on_char ' ' (read_line ()) |> List.map int_of_string in
  let cnts =
    let mods = Array.make m 0 in
    let rec find_mods prev = function
      | [] -> ()
      | h :: t ->
        let p_sum_mod_m = (prev + h) mod m in
        mods.(p_sum_mod_m) <- mods.(p_sum_mod_m) + 1;
        find_mods p_sum_mod_m t
    in
    find_mods 0 lst;
    mods
  in
  cnts.(0) <- cnts.(0) + 1;
  let res = Array.fold_left (fun acc n -> acc + nC2 n) 0 cnts in
  print_int res
;;
