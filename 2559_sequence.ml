let read_pair () =
  let input = read_line () in
  Scanf.sscanf input "%d %d" (fun x y -> x, y)
;;

let take_drop n lst =
  let rec take_drop_aux n lst acc =
    if n > 0
    then take_drop_aux (n - 1) (List.tl lst) (List.hd lst :: acc)
    else List.rev acc, lst
  in
  take_drop_aux n lst []
;;

let sum = List.fold_left ( + ) 0

let () =
  let _tot_days, consec_days = read_pair () in
  let temps = String.split_on_char ' ' (read_line ()) |> List.map int_of_string in
  let init_window_lst, remnant = take_drop consec_days temps in
  let init_window_sum = sum init_window_lst in
  let res =
    let rec slide window remnant prev_window_sum max_window_sum =
      match remnant with
      | [] -> max_window_sum
      | h :: t ->
        let pop = Queue.pop window in
        Queue.push h window;
        let cur_window_sum = prev_window_sum - pop + h in
        slide window t cur_window_sum (max max_window_sum cur_window_sum)
    in
    let init_window = Queue.create () in
    List.iter (Fun.flip Queue.push @@ init_window) init_window_lst;
    slide init_window remnant init_window_sum init_window_sum
  in
  print_int res
;;
