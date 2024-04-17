let () =
  let n = read_int () in
  let inputs =
    String.split_on_char ' ' (read_line ()) |> List.map int_of_string
  in
  let lst = List.combine inputs (List.init n @@ Fun.const 1) in
  let res =
    let rec find_lis prev_rev next lis_hitherto =
      match next with
      | [] -> lis_hitherto
      | (elem, _) :: rem ->
          let lis_incl_cur =
            List.fold_left
              (fun acc (target, lis_incl_target) ->
                if target < elem then max acc (1 + lis_incl_target) else acc)
              1 prev_rev
          in
          find_lis ((elem, lis_incl_cur) :: prev_rev) rem (max lis_hitherto lis_incl_cur)
    in
    find_lis [] lst Int.min_int
  in
  print_int res
