let rec find_lis prev_rev next lis_hitherto =
  match next with
  | [] -> lis_hitherto
  | (cur_elem, _) :: rem ->
      let lis_incl_cur =
        List.fold_left
          (fun acc (target, lis_incl_target) ->
            if target < cur_elem then max acc (1 + lis_incl_target) else acc)
          1 prev_rev
      in
      find_lis
        ((cur_elem, lis_incl_cur) :: prev_rev)
        rem
        (max lis_hitherto lis_incl_cur)

let rec read_pairs n acc =
  if n < 1 then acc
  else
    let input = read_line () in
    let wire = Scanf.sscanf input "%d %d" (fun x y -> (x, y)) in
    read_pairs (n - 1) (wire :: acc)

let () =
  let n = read_int () in
  let wires =
    read_pairs n [] |> List.fast_sort compare
  in
  let lst = List.combine (snd @@ List.split wires) (List.init n (Fun.const 1)) in
  let res = find_lis [] lst Int.min_int in
  print_int @@ n - res
